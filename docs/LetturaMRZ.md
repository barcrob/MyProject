

# Lettura OCR dell’MRZ

## Prerequisiti
E’ importante ricordare che nonostante il framework supporti sistemi operativi pari o successivi alla versione *iOS 9*, questa funzionalità richiede almeno una versione ***iOS 10*** per poter essere eseguita.

Per un corretto funzionamento di questa funzionalità del framework occorre anche inserire nel file plist dell’applicativo la seguente entry:

![MRZPermissionPlist](MRZPermissionPlist.png)

	<key>NSCameraUsageDescription</key>
	<string>Consenti l&apos;accesso per poter inquadrare il QR Code</string>

dove la stringa da inserire come valore deve essere una frase che spieghi chiaramente all’utente il motivo per cui l’applicativo ha bisogno dell’autorizzazione all’utilizzo della fotocamera.



## Utilizzo
Nell’utilizzo di questa funzionalità del framework sono coinvolti i seguenti componenti:

 - *PIProcessMRZViewController* : il view controller che gestisce la lettura ottica della banda MRZ del documento elettronico.
 - *PIProcessMRZ*: lo storyboard che contiene il `PIProcessMRZViewController`; il bundleID è *it.poste.mrtdframework.posteMRTDFramework*


Per utilizzare la funzionalità di lettura ottica dell’MRZ tramite il framework occorre caricare il viewController che esegue tale acquisizione. Per caricare il controller: 

 1. Linkare lo storyboard `PIProcessMRZ` su un’action (esempio: pulsante), oppure istanziare lo storyboard PIProcessMRZ con il metodo `[UIStoryboard storyboardWithName:… bundle:…]` utilizzando il bundle *it.poste.mrtdframework.posteMRTDFramework*
 2. Recuperare dallo storyboard il riferimento al
    `PIProcessMRZViewController` mediante il metodo prepareForSegue…, o mediante il metodo `instantiateInitialViewController` dell’oggetto storyboard (se lo storyboard è stato linkato manualmente nel codice)

Dopo aver recuperato il riferimento al viewController è necessario impostare come suo delegato  un oggetto conforme al protocollo `ProcessMRZProtocol`. Tale protocollo definisce le varie callback che consentono al delegato di ricevere il risultato dell’operazione di lettura ottica.

Il controller espone anche un outlet che consente di impostare il titolo della view:

    @IBOutlet public weak var titleLabel: UILabel!


**Esempio** di customizzazione del controller:

    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:STORYBOARD_NAME bundle:nil];
                   
    PIProcessMRZViewController *detectMRZViewController = [storyboard instantiateViewControllerWithIdentifier:CONTROLLER_STORYBOARD_ID];
    
    detectMRZViewController.delegate = self;
  
    [detectMRZViewController.titleLabel setAttributedText:customAttributedText];


Una volta presentata la view del controller il framework avvia il riconoscimento ottico, il cui esito dipende da diversi fattori (se l’utente inquadra correttamente la banda MRZ del documento o meno, presenza di riflessi sul documento). Dopo circa 5 secondi se il riconoscimento non è ancora avvenuto con successo, l’utente vede apparire sul display un countdown di ulteriori 5 secondi durante i quali il framework continua nel suo tentativo di lettura. Se allo scadere di questi ulteriori 5 secondi l’operazione ancora non si è conclusa il framework la interrompe e provvede a scattare una foto del documento. Entrambi i timer di 5 secondi utilizzati nel funzionamento di questo controller sono cablati nel framework e quindi non configurabili.

Pertanto l’operazione in questione può avere due esiti:
 

 - riconoscimento della stringa MRZ e acquisizione dell’immagine del documento,
 - riconoscimento fallito e acquisizione comunque dell’immagine del documento.

 Nel primo caso viene invocata la seguente callback:

    - (void)detectedMRZWithMrz:(NSString * _Nonnull)mrz documentNumber:(NSString * _Nonnull)documentNumber birthDate:(NSDate * _Nullable)birthDate expiryDate:(NSDate * _Nullable)expiryDate img:(UIImage * _Nonnull)img sender:(id _Nullable)sender;

In tal caso, come si vede dalla firma del metodo, il controller del framework restituisce diverse informazioni: 

 - la stringa MRZ,
 - il numero del documento,
 - la data di nascita
 - la data di scadenza del documento
 - l’immagine del documento catturata all’istante dell’avvenuto
   riconoscimento ottico
 - un riferimento al controller che sta inviando la notifica (il
   `PIProcessMRZViewController`)

**Esempio** di gestione della callback di esito positivo

    - (void)detectedMRZWithMrz:(NSString * _Nonnull)mrz documentNumber:(NSString * _Nonnull)documentNumber birthDate:(NSDate * _Nullable)birthDate expiryDate:(NSDate * _Nullable)expiryDate img:(UIImage * _Nonnull)img sender:(id _Nullable)sender{
        self.mrz = mrz;
        self.documentNumber = documentNumber;
        self.birthDate = birthDate;
        self.expiryDate = expiryDate;
    
        //Salvataggio dell’immagine in un opportuno path
        NSString * path = [self saveMRZImage:img];
    
         //Salvataggio delle informazioni relative all’immagine nel framework
         NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
         PIImage * image = [[PIImage alloc]initWithResourceType:_LOCAL description:@“Retro CIE” hash:fileHash file: path];
         [[PIMRTDDataHelper sharedInstance]addPIImage: image];
    }


Nel secondo caso invece il controller restituisce solo un’immagine del documento tramite la seguente callback:

    (void)notDetectedMRZWithImg:(UIImage * _Nullable)img sender:(id _Nullable)sender;


Quindi i parametri restituiti sono:

 - L’immagine del documento catturata allo scattare del timer,
 - un riferimento al controller che sta inviando la notifica (il
   `PIProcessMRZViewController`)

**Esempio** di gestione della callback di esito negativo

    - (void)notDetectedMRZWithImg:(UIImage * _Nullable)img sender:(id _Nullable)sender {
         [self resetMRZProperties];
         
         //Salvataggio dell’immagine in un opportuno path
         NSString * path = [self saveMRZImage:img];
    
         //Salvataggio delle informazioni relative all’immagine nel framework
         NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
         PIImage * image = [[PIImage alloc]initWithResourceType:_LOCAL description:@“Retro CIE” hash:fileHash file: path];
         [[PIMRTDDataHelper sharedInstance]addPIImage: image];
    
    }

Come si può vedere dai precedenti esempi è cura dell’applicativo client gestire il salvataggio dell’immagine restituita dalle callback sul file system per i successivi usi. Oltre al salvataggio l’applicativo ha la responsabilità di gestire la cancellazione dello stesso file al fine di garantire la consistenza dei dati raccolti.

Il salvataggio in persistenza tramite la classe `PIMRTDDataHelper` garantisce l’inserimento del file appena salvato nell’archivio compresso che il framework invierà in upload al beck-end.

**N.B.** Se l’applicativo passa nello stato di Inactive, il processo di scansione del documento elettronico viene interrotto e il controller `PIProcessMRZ` invia un evento di `notDetectedMRZWithImg` con l’immagine catturata all’istante della transizione in questo stato. Sarà compito dell’applicativo gestire nel modo che ritiene più opportuno in base al contesto tale evento.


Inoltre il protocollo mette a disposizione la seguente callback per la navigazione:

    (void)didPressedBackMRZWithSender:(id _Nullable)sender;

Questo metodo viene utilizzato dal framework per notificare all’applicativo client che l’utente ha premuto il pulsante BACK sul controller `PIProcessMRZViewController`. E’ poi compito dell’app gestire tale evento così come tutta la navigazione del controller (presentazione e dismissione).

**Esempio** di gestione dell’evento di Back

    - (void)didPressedBackMRZWithSender:(id _Nullable)sender {   
    	[self resetMRZProperties];    
    	[self.navigationController popViewControllerAnimated:YES];
    }



Infine il protocollo definisce altri due metodi che vengono usati dal framework per dare la possibilità all’applicativo client di gestire, se necessario, i permessi della fotocamera (tramite cui avviene la lettura ottica dell’MRZ). 

    - (void)userDidDenyVideoPermissionWithSender:(id _Nullable)sender;
    - (void)notVideoPermissionAvailableWithSender:(id _Nullable)sender;

Contestualmente al caricamento del `PIProcessMRZViewController` il framework verifica la presenza dei permessi eventualmente forniti in precedenza dall’utente per l’accesso alla fotocamera, oppure interroga l’utente in caso di primo utilizzo della fotocamera da parte dell’applicativo. Quindi  in assenza di tali permessi notifica tale situazione all’applicativo.
Più in particolare, se l’utente aveva precedentemente negato i permessi viene invocata la callback `notVideoPermissionAvailableWithSender`, se invece l’utente viene interrogato per la prima volta al riguardo e decide di negare i permessi, viene invocata la callback `userDidDenyVideoPermissionWithSender`. 

**Esempio** di gestione della negazione dei permessi da parte dell’utente al primo utilizzo della fotocamera

    - (void)userDidDenyVideoPermissionWithSender:(id _Nullable)sender {
        [self.navigationController popViewControllerAnimated:YES];
    }



**Esempio** di gestione di assenza permessi da parte dell’utente per scelta precedente.

    - (void)notVideoPermissionAvailableWithSender:(id _Nullable)sender{
    
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Avviso"
                                   message:@"Sembra che tu non abbia dato il permesso per utilizzare la fotocamera"
                                   preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
       handler:^(UIAlertAction * action) {}];
    
    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
    
    }

