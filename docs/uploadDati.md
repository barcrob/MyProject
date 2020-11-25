


## UPLOAD DEI DATI
Per effettuare l’upload dei dati verso il sistema EID il framework mette a disposizione la classe `PIEidService`.  L’interfaccia di questa classe consta dei seguenti metodi:

    -(id) initWithBaseURL:(nonnull NSString *) baseURL skipSSL:(BOOL) skipSSL;
    -(void)uploadCompletion:(PIUploadCompletion) completion;

Il metodo `initWithBaseURL` consente di inizializzare la classe PIEidService in base ai seguenti parametri:

 - *baseURL* : la base url del servizio di BE
 - *skipSSL*: un flag che varrà true in collaudo, false in produzione.

Il metodo uploadCompletion consente si effettuare l’upload dei dati e di impostare tramite il parametro *completion* un blocco di codice da far eseguire al framework sulla risposta http. Tale parametro è di tipo `PIUploadCompletion` così definito:

    typedef void (^PIUploadCompletion)(PIReturnData *returdData);

Questo vuol dire che l’esito del processo di updoad è comunicato all’applicativo tramite il parametro *returnData*. Infatti il tipo `PIReturnData` è definito come una classe con le seguenti properties:

 - *status*: una stringa che conterrà “0” in caso di esito positivo, “-1”
   in caso di esito negativo
 - *code*: una stringa che conterrà un codice numerico secondo
   un’opportuna codifica
 - *message*: un’eventuale descrizione dell’errore, oppure stringa vuota

I possibili codici di errore sono i seguenti:

| Codice | Descrizione |
|--|--|
| 10000 |  Mancata valorizzazione di un parametro mandatario (eidPubKeyB64 o eidAzCodeB64Error o codeVerify)|
| 10008 |  Mancata valorizzazione del parametro docType|
| 10005 |  Errore nella creazione dello zip|
| 10006 |  Errore nella cifratura dello zip|
| 10007 | Errore generico|


Per poter effettuare l'upload verso il sistema EID è necessario seguire i seguenti passi:

 1. Gestire correttamente il salvataggio in persistenza delle strutture 
    dati relative alle immagini (PIImage e PIImageMatch) come descritto 
    precedentemente nelle varie fasi di acquisizione.
 2. Garantire la consistenza dei file salvati sul file system e dei dati
   memorizzati negli UserDefaults tramite la classe PIMRTDDataHelper;
   sono tali dati infatti a determinare la composizione del file
   compresso da inviare al Backend, è quindi cura dell’applicativo
   garantire che al momento dell’upload gli UserDefaults contengano
   tutti e soli i dati che devono essere inviati.
 3. Richiamare il metodo getCodeAppChallenge di PIMRTDDataHelper per
   ottenere il code challenge
 4. Ottenere e settare il valore di eidPubKeyB64
 5. Ottenere e settare il valore di eidAzCodeB64
 6. Settare il tipo di documento (es: `[PIMRTDDataHelper sharedInstance].docType = @"ci";` )
 7. Inizializzare PIEidService (es: `PIEidService *uploadService = [[PIEidService alloc] initWithBaseURL:@"http://BASE_URL/jod-electronic-id" skipSSL:false];` )
 8. Utilizzare il metodo uploadCompletion: di `PIEidService`

Il metodo updloadCompletion effettua una verifica preliminare sulla presenza dei dati mandatori. Quindi crea un file compresso contenente al proprio interno i file salvati durante la sessione dell’app (relativi alle varie immagini precedentemente acquisite) e un file json che ne descrive il contenuto, provvede a cifrare il file compresso e infine lo invia in upload.

Il file compresso e quello risultante dalla cifratura di quest’ultimo vengono scritti in una specifica sottocartella di Documents. Il nome di tale cartella sarà quello inizialmente impostato dall’applicativo (nell’attributo *dataFolderName* della classe `PIMRTDDataHelper`) oppure in assenza di tale impostazione nella cartella di default *MRTD*. 

Sarà cura dell’applicativo gestire la cancellazione di questi file (o dell’intera cartella) quando non più necessari.

**NOTA**: in seguito ad una chiamata effettuata con successo al metodo di upload, l'access token sarà salvato in persistenza tramite l’apposito metodo della classe `PIMRTDDataHelper`.

#### Esempio 

    -(void)someMethod{
    
        // Gestire immagini e persistenza locale
    
        ...
    
        // Ottenere code app challenge
    
        NSString *codeAppChallenge = [[PIMRTDDataHelper sharedInstance] getCodeAppChallenge];
    
        // Ottenere eidAzCodeB64 e eidPubKeyB64
    
        // Settare eidAzCodeB64 e eidPubKeyB64
    
        [PIMRTDDataHelper sharedInstance].eidAzCodeB64 = @"b64AzCodeString";
        [PIMRTDDataHelper sharedInstance].eidPubKeyB64 = @"b64PubKeyString";
    
        // Settare tipo documento
        [PIMRTDDataHelper sharedInstance].docType = @"ci";
        
        PIEidService *uploadService = [[PIEidService alloc] initWithBaseURL:@"http://BASE_URL/jod-electronic-id" skipSSL:false];
        [uploadService uploadCompletion:^(PIReturnData * _Nonnull returdData) {
           
            NSLog(@"... completed upload!!!");
    
            // In caso di successo il PIReturnData avrà uno status "0" e l'access token restituito dalla chiamata di upload sarà disponibile tramite il metodo getAccessToken della classe 
    PIMRTDDataHelper         
    
        }];
    
        ...
    }

