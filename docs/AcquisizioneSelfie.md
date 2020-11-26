

# Acquisizione foto utente (selfie) mediante FaceDetection

Componenti coinvolti:

 - `PIFaceDetection`: lo storyboard che contiene il
   PIFaceDetectionViewController, il bundleID è
   *it.poste.mrtdframework.posteMRTDFramework*
 - `PIFaceDetectionViewController` : il view controller che esegue lo scatto fotografico una volta riconosciuto la presenza di un volto umano mediante FaceDetection
 - *String* *Path* della foto acquisita: il path al file dal quale leggere
   l’immagine acquisita
 - `PIMRTDDataHelper`: singleton che gestisce la conservazione dei dati raccolti

La funzionalità di Face Detection consente di catturare in automatico la foto di una persona quando viene rilevato il viso della stessa.

## Impostazioni Grafiche
Il controller espone alcune properties che permettono di customizzare l’aspetto grafico:

 - `faceDetectedText`: di tipo NSString, permette di impostare un titolo non formattato
 - `faceDetectedTextAttributed`: di tipo NSAttributedString, permette di impostare un titolo formattato
 - `faceDetectedColor`: di tipo UIColor, permette di impostare il colore assunto dall’ovale in tutti gli istanti in cui vengono riconosciuti i tratti di un volto nell’immagine inquadrata; il valore di default è verde

La property `faceDetectedText` ha la priorità rispetto alla property `faceDetectedTextAttributed`.


**Esempio** di customizzazione del controller:
 

    - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    	PIFaceDetectionViewController *faceDetectionController = (PIVideoCamera *) [segue destinationViewController];
    	faceDetectionController.delegate = self;
    
    	faceDetectionController.faceDetectedTextAttributed = customTextAttributedString;
    	faceDetectionController.faceDetectedColor = customUIColor;
    
    }


Il processo di acquisizione della foto utente si divide in due parti:

## Acquisizione della foto

Per acquisire la foto utente (selfie) è necessario caricare il viewController adibito al scatto della foto mediante fotocamera frontale. Per caricare il controller: 

 1. Linkare lo storyboard PIFaceDetection su un’action (esempio: pulsante), oppure istanziare lo storyboard PIFaceDetection con il metodo `[UIStoryboard` `storyboardWithName`:… `bundle`:…]` utilizzando il
    *bundle it.poste.mrtdframework.posteMRTDFramework*
 2. Recuperare dallo storyboard il riferimento al
    `PIFaceDetectionViewController` mediante il metodo `prepareForSegue`…, o mediante il metodo `instantiateInitialViewController` dell’oggetto storyboard (se lo storyboard è stato linkato manualmente nel codice)

Dopo aver recuperato il riferimento al ViewController è necessario settare un oggetto delegato conforme al protocollo `IFaceDetectionProtocol`. Sarà tale delegato a recepire il risultato dello scatto della fotocamera. Dopo l’acquisizione di una foto il `PIFaceDetectionViewController` comunicherà infatti al suo delegato il path della foto salvata sul file system. l’App dovrà dunque recuperare la foto tramite tale path per poterla visualizzare o inviare verso altri sistemi (esempio sistema di BE, cloud, ecc…).  
Il path in cui viene salvata la foto punta ad una sottocartella di nome *FaceDetection*, mentre il nome del file è composto dalla stringa *FaceDetected* concatenata con un timestamp. La sottocartella *FaceDetection* verrà creata all’interno della cartella il cui nome è stato inizialmente impostato dall’applicativo (nell’attributo `dataFolderName` della classe `PIMRTDDataHelper`) oppure in assenza di tale impostazione nella cartella di default *MRTD*.

**NOTA**: è compito dell’App gestire il ciclo di vita del `PIFaceDetectionViewController` (navigazione, presentazione, dismissione, ecc…) 


## Gestione della persistenza della foto
Al fine di garantire l’invio della foto appena scattata verso il back-end nella fase di upload, l’applicativo dovrà creare un oggetto `PIImageMatch` e settarlo all’interno dell’oggetto singleton `PIMRTDDataHelper`. 

Nel caso di immagini ospitate su azure l’oggetto `PIImageMatch` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: `AZURE`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il token azure

Nel caso di immagini ospitate sul cloud l’oggetto `PIImageMatch` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: URI
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file immagine PRIMA del caricamento sul cloud
 - *file*: il link alla risorsa sul cloud

Nel caso di immagini sul quale deve essere eseguito l’upload sul sistema di BE collegato alla libreria (jod-electroinc-id BE) l’oggetto `PIImageMatch` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: LOCAL
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il path al file system restituito dal `PIFaceDetectionViewController`

**Esempio** gestione di una foto da inviare su jod-electronic-id BE:

        -(void)pictureTakenAtPath:(NSString *)path sender:(id) sender {
            
            if (path) {
                NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
                PIImageMatch * imageMatch = [[PIImageMatch alloc]initWithResourceType:LOCAL description:@"Selfie" hash:fileHash file:path];
                [[PIMRTDDataHelper sharedInstance]addImageMatch:imageMatch];
            }
        ...
    }

**Esempio**  gestione di una foto caricata su cloud:

    -(void)pictureTakenAtPath:(NSString *)path sender:(id) sender {
        
        if (path) {
            NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
            PIImageMatch * imageMatch = [[PIImageMatch alloc]initWithResourceType:URI description:@"Selfie" hash:fileHash file:@"https://link_a_una_risorsa_su_cloud"];
            [[PIMRTDDataHelper sharedInstance]addImageMatch:imageMatch];
        }
        ...
    }





