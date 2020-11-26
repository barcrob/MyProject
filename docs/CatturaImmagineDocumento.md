

# Cattura dell'immagine di un documento
Questa funzionalità permette all’applicativo di acquisire l’immagine di un documento elettronico o cartaceo tramite un controller messo a disposizione del framework.

## Prerequisiti 

Per un corretto funzionamento di questa funzionalità del framework occorre inserire nel file plist dell’applicativo la seguente entry:

![CameraUsageDescription](CameraUsageDescription.png)

	<key>NSCameraUsageDescription</key>
	<string>Consenti l&apos;accesso per poter inquadrare il QR Code</string>

dove la stringa da inserire come valore deve essere una frase che spieghi chiaramente all’utente il motivo per cui l’applicativo ha bisogno dell’autorizzazione all’utilizzo della fotocamera.


## Utilizzo
Nell’utilizzo di questa funzionalità del framework sono coinvolti i seguenti componenti:

 - *PICameraViewController* : il view controller che gestisce
   l’acquisizione dell’immagine tramite la fotocamera del device.
 - *PICamerShot*: lo storyboard che contiene il `PICameraViewController`; il bundleID è *it.poste.mrtdframework.posteMRTDFramework*
 - *PIMRTDDataHelper*: singleton che gestisce la conservazione dei dati raccolti

Per utilizzare questa funzionalità occorre caricare il viewController che esegue tale acquisizione. Per caricare il controller: 

 1. Linkare lo storyboard PICamerShot su un’action (esempio: pulsante), oppure istanziare lo storyboard PICamerShot con il metodo`[UIStoryboard storyboardWithName:… bundle:…]` utilizzando il bundle *it.poste.mrtdframework.posteMRTDFramework*
 2. Recuperare dallo storyboard il riferimento al
    `PIProcessMRZViewController` mediante il metodo *prepareForSegue*…, o mediante il metodo *instantiateInitialViewController* dell’oggetto storyboard (se lo storyboard è stato linkato manualmente nel codice)

## Impostazioni grafiche 

Grazie ad alcune properties esposte dal framework l’applicativo può  configurare vari aspetti di questo viewController:
	

 - *cameraTitle*, di tipo NSString: permette di impostare un titolo non formattato
 - *cameraAttributedTitle*, di tipo NSAttributedString: permette di impostare un titolo formattato
 - *cameraTitleLabel*, un’outlet di tipo UILabel; permette di impostare il titolo direttamente puntando all’elemento grafico dello storyboard
 - *imgFilename*, di tipo NSString; permette di personalizzare il nome del file che conterrà l’immagine acquisita.

N.B. Se nessuno dei due attributi, `cameraTitle` o `cameraAttributedTitle`, viene impostato resta il valore di default impostato da storyboard per il titolo che è “*Inquadra la pagina con la foto del tuo documento elettronico*”. Inoltre il valore impostato sull’attributo `cameraTitle` ha la precedenza su `cameraAttributedTitle`.




## Gestione degli eventi di acquisizione della foto

Dopo aver recuperato il riferimento al viewController è necessario impostare come suo delegato  un oggetto conforme al protocollo `ICameraControllerProtocol`. Tale protocollo è così definito:


    @protocol ICameraControllerProtocol <NSObject, PINavigationProtocol, PIAuthorizationStatusProtocol>
    -(void)cameraViewControllerDidShot:(id)sender atPath:(NSString *) path;
    @end

Come si può vedere il protocollo aggiunge ai metodi degli altri protocolli ereditati la definizione della callback `cameraViewControllerDidShot`, che consente al delegato di ricevere il risultato dell’operazione di acquisizione della foto.

Come argomenti della callback vengono passati:
  

 - Un riferimento al controller chiamante (PICameraViewController)
 - Il path dell’immagine salvata dal framework

**N.B**. Il salvataggio sul fileSystem dell’immagine acquisita è gestito direttamente dal framework, come si può notare dal fatto che la callback restituisce un path e non un’immagine.  Il path in questione punterà ad una sottocartella di nome *Frameshot* (non configurabile), mentre il nome del file è quello impostato nella property `imgFilename` al quale viene poi concatenato un timestamp. In assenza di un valore fornito tramite la property  `imgFilename` viene utilizzato come valore di default la stringa “*Frameshot-*“. La sottocartella Frameshot verrà creata all’interno della cartella il cui nome è stato inizialmente impostato dall’applicativo (nell’attributo `dataFolderName` della classe `PIMRTDDataHelper`) oppure in assenza di tale impostazione nella cartella di default *MRTD*

Il framework offre anche un altro strumento in alternativa all’implementazione di questa callback per permettere all’applicativo di ricevere notifica dell'evento di acquisizione foto. 
Il controller `PICameraViewController` infatti ha un attributo in cui l’applicativo può impostare un blocco di codice che il framework provvederà a mandare in esecuzione in corrispondenza dell’evento di cui sopra:

 - *didShotBlock*: permette all’applicativo di definire il blocco di codice che il framework dovrà eseguire quando l’utente preme il tasto per l’acquisizione della foto.

 Tale attributi è così definito:

    @property (nonatomic, strong) cameraViewControllerDidShotCompletionBlock didShotBlock;


Dove i tipi utilizzati nella definizione sono a loro volta così definiti:

    typedef void (^ cameraViewControllerDidShotCompletionBlock) (UIViewController *sender, NSString *path);

Quindi come si può vedere, gli argomenti di questo blocco ricalcano esattamente gli argomenti della callback precedente.



## Gestione della persistenza della foto

Una volta recuperata la foto dal file system, l’applicativo crea un oggetto associato `PIImage` e lo salva in persistenza tramite la classe `PIMRTDDataHelper`. Ciò permette il successivo inserimento della foto all’interno dell’archivio compresso che verrà inviato in upload al back-end.

Nel caso di immagini ospitate su azure l’oggetto `PIImage` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: _AZURE, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il token azure

Nel caso di immagini ospitate sul cloud l’oggetto `PIImage` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: _URI, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file immagine PRIMA del caricamento sul cloud
 - *file*: il link alla risorsa sul cloud

Nel caso di immagini sul quale deve essere eseguito l’upload sul sistema di BE collegato alla libreria (jod-electroinc-id BE) l’oggetto `PIImage` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: LOCAL, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il path al file restituito dal `PICameraViewController`

**Esempio** di gestione dell’evento acquisizione foto.

    -(void)cameraViewControllerDidShot:(id)sender atPath:(NSString *) path
    {
        self.path = path;
        UIImage *picture = [UIImage imageWithContentsOfFile:path];
    
        if (path) {
            NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
            PIImage * image = [[PIImage alloc]initWithResourceType:_LOCAL description:@“Fronte CIE” hash:fileHash file: path];
            [[PIMRTDDataHelper sharedInstance]addPIImage: image];
        }
    
    
        GenericPictureViewController *nextVC = [[UIStoryboard storyboardWithName:@"Registration" bundle:nil]instantiateViewControllerWithIdentifier:@“genericPictureViewControllerStoryboardID"];
        nextVC.picture = picture;
        [self.navigationController pushViewController:nextVC animated:true];
    }

## Gestione degli eventi di di navigazione

Per quanto riguarda la gestione degli eventi di navigazione, il `PICameraViewController` notifica l’evento di pressione del tasto BACK tramite il metodo `PIdidPressedBack` che il protocollo `ICameraControllerProtocol` eredita dal protocollo `PINavigationProtocol`.

    @protocol PINavigationProtocol <NSObject>
    -(void)PIdidPressedBack:(id)sender;
    @end

**Esempio** di gestione del tasto Back

    -(void)PIdidPressedBack:(id*)sender
    {
        [self resetResidenzaPassaportoImage];
        [self.navigationController popViewControllerAnimated:YES]
    }


Il framework offre anche un altro strumento in alternativa all’implementazione di questa callback per permettere all’applicativo di gestire l’evento di pressione del tasto Back. 
Il controller `PICameraViewController` infatti ha un attributo in cui l’applicativo può impostare un blocco di codice che il framework provvederà a mandare in esecuzione in corrispondenza dell’evento in questione:

 - *didPressedBackBlock*: permette all’applicativo di definire il codice che il framework dovrà eseguire quando l’utente preme il bottone di BACK.

 Tale attributo è così definiti:

    @property (nonatomic, strong) PIdidPressedBackCompletionBlock didPressedBackBlock;

Dove i tipi utilizzati nella definizione sono a loro volta così definiti:

    typedef void (^ PIdidPressedBackCompletionBlock) (UIViewController *sender);

Quindi come si può vedere, gli argomenti di questo blocco ricalcano esattamente gli argomenti della callback precedente.


## Gestione dei permessi della fotocamera

La notifica dello stato dei permessi di accesso alla fotocamera viene fatta utilizzando un apposito protocollo, comune a più controller del framework. Si tratta del protocollo `PIAuthorizationStatusProtocol`, da cui `ICameraControllerProtocol` eredita.

    @protocol PIAuthorizationStatusProtocol <NSObject>
    -(void)userDidDenyVideoPermission:(id)sender;
    -(void)userDidDenyAudioPermission:(id)sender;
    -(void)notVideoPermissionAvailable:(id)sender;
    -(void)notAudioPermissionAvailable:(id)sender;
    @end


Contestualmente al caricamento del `PICameraViewController` il framework verifica la presenza dei permessi eventualmente forniti in precedenza dall’utente per l’accesso alla fotocamera, oppure interroga l’utente in caso di primo utilizzo della fotocamera da parte dell’applicativo. Quindi  in assenza dei permessi necessari notifica tale situazione all’applicativo.

Più in particolare, se l’utente aveva precedentemente negato i permessi viene invocata la callback `notVideoPermissionAvailable`, se invece l’utente viene interrogato per la prima volta al riguardo e decide di negare i permessi, viene invocata la callback `userDidDenyVideoPermission`. 
Naturalmente per  la sola acquisizione di immagini i permessi da verificare sono solo quelli video e non quelli audio.

**Esempio** di gestione della negazione dei permessi da parte dell’utente al primo utilizzo della fotocamera

    -(void)userDidDenyVideoPermission:(id)sender{
        [self.navigationController popViewControllerAnimated:YES];
    }

**Esempio** di gestione di assenza permessi da parte dell’utente per scelta precedente.

    -(void)notVideoPermissionAvailable:(id)sender {
    
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Avviso"
                                   message:@"Sembra che tu non abbia dato il permesso per utilizzare la fotocamera"
                                   preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
       handler:^(UIAlertAction * action) {}];
    
    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
    
    }


