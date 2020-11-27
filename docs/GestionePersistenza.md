

## Indice
[GESTIONE DEI DATI E PULIZIA DELLA PERSISTENZA](#title1)

    [La classe PIMRTDDataHelper: gestione dei dati](#title2)

[GESTIONE DATI CON PERSISTENZA](#title3)

    [Gestione delle strutture dati relative alle immagini acquisite](#title4)

    [Gestione delle strutture dati relative al chip del documento elettronico](#title5)

    [Gestione dei dati relativi all'anagrafica](#title6)

    [Gestione dei dati relativi a MRZ, tipo di documento elettronico, accessToken](#title7)

    [Gestione persistenza generale](#title8)

[GESTIONE DATI NON PERSISTENTI](#title9)


[METODI DI UTILITY](#title10)


 





 <div id='title1'/>
 
## GESTIONE DEI DATI E PULIZIA DELLA PERSISTENZA 
Il framework raccoglie e persiste dati sul file system rendendoli disponibili al chiamante per l'utilizzo nello specifico contesto applicativo (esempio: visualizzazione a video, invio verso sistemi di BE, ecc...); la cancellazione della persistenza dei dati (file su disco e strutture dati negli UserDefaults) generati dal framework è interamente demandata all'applicativo. In questo modo sarà l'applicativo a decidere quando richiedere i dati e a gestirne la relativa cancellazione. 

Per quanto riguarda in particolare il file system, il framework crea una sottocartella della directory Documents del dispositivo, il cui nome è configurabile. A tal fine è necessario impostare la seguente property della classe `PIMRTDDataHelper`:

    @property (nonatomic, strong) NSString* dataFolderName;

Se l’applicativo non imposta alcun valore il framework utilizza di default la stringa “*MRTD*”.

La cancellazione di questa directory è completamente demandata all’applicativo. Anche la rimozione delle strutture dati in persistenza è responsabilità dell’applicativo, ma il framework mette a disposizione a tal fine dei metodi specifici.
Di seguito sono riportati alcuni esempi di possibili momenti in cui eseguire le suddette cancellazioni:

 - cancellazione dei dati ad ogni avvio del flusso di acquisizione
 - cancellazione dati alla fine dell’upload verso il BE
 - cancellazione puntuale dei dati acquisiti (solo video, solo foto, ecc…). Ad esempio se l’utente decide di procedere ad una nuova acquisizione dello stesso dato, al fine di evitare la duplicazione dello stesso occorre cancellare la precedente acquisizione

 <div id='title2'/>
 
### La classe PIMRTDDataHelper: gestione dei dati
La classe singleton `PIMRTDDataHelper` ha il compito di mantenere i riferimenti alle strutture dati, file, e informazioni create dalla libreria durante il suo utilizzo e fornire dei metodi per la gestione della persistenza dei dati da essa raccolti. La persistenza viene garantita tramite il salvataggio delle strutture dati negli UserDefaults, ciascuna con una specifica chiave.

I riferimenti in tal modo creati dalla classe `PIMRTDDataHelper` alle risorse (foto e altre informazioni di seguito descritte) verranno utilizzate dallo stesso framework per la creazione del file compresso da inviare in upload al back-end.

La classe PIMRTDDataHelper gestisce sia il salvataggio di dati in persistenza sia la memorizzazione di alcuni dati non persistenti.

 <div id='title3'/>
 
## GESTIONE DATI CON PERSISTENZA

 <div id='title4'/>
 
### Gestione delle strutture dati relative alle immagini acquisite
Per la gestione delle informazioni relative alle immagini acquisite il framework utilizza delle apposite strutture dati di cui è garantita la persistenza (tramite salvataggio negli *UserDefaults*).

In particolare la classe  `PIImageMatch` viene utilizzata per contenere le informazioni relative alla foto dell’utente (*selfie*). 

La classe `PIMRTDDataHelper` mette a disposizione i seguenti metodi per il salvataggio in persistenza di un oggetto di tipo `PIImageMatch`:

 - *addPIImageMatch*: aggiunta sull’helper di un `PIImageMatch`
 - *getPIImageMatches*: get del `PIImageMatch`
 - *deletePIImageMatches*: cancellazione di un oggetto `PIImageMatch`

Di seguito le firme dei metodi di cui sopra:

    -(void) addPIImageMatch:(nonnull PIImageMatch *) imageMatch;
    -(NSMutableArray <PIImageMatch *> *) getPIImageMatches;
    -(void) deletePIImageMatches;

La classe `PIImage` viene invece utilizzata per contenere le informazioni relative alle foto del documento dell’utente. 

La classe `PIMRTDDataHelper` mette a disposizione i seguenti metodi per il salvataggio in persistenza di un oggetto di tipo `PIImage`:

 - *addPIImage*: aggiunta sull’helper di un `PIImage`
 - *getPIImages*: get del `PIImage`
 - *deletePIImages*: cancellazione del `PIImage`

Di seguito le firme dei metodi di cui sopra:

    -(void) addPIImage:(PIImage*)image;
    -(NSMutableArray <PIImage*> *) getPIImages;
    -(void) deletePIImages;


In caso di documento cartaceo per indicare al Backend la foto con cui effettuare il *FaceMatch* occorre usare i seguenti metodi per il salvataggio in persistenza:

 - *addDataCartPIImage*: aggiunta sull’helper di un `PIImage`
 - *getDataCartPIImage*: get del `PIImage`
 - *deleteDataCartPIImage*: cancellazione del `PIImage` persistenza

Di seguito le firme dei metodi di cui sopra:

    -(void) addDataCartPIImage:(PIImage*)image;
    -(PIImage*) getDataCartPIImage;
    -(void) deleteDataCartPIImage;


 <div id='title5'/>
 
### Gestione delle strutture dati relative al chip del documento elettronico

Per la gestione della persistenza delle strutture dati relative al chip del documento elettronico la classe `PIMRTDDataHelper` mette a disposizione i seguenti metodi:

 - *setDG1B64*: per salvare la stringa relativa al DG1 codificata in base
   64
 - *getDG1B64*: get della stringa relativa al DG1 codificata in base 64
 - *deleteDG1B64*: cancellazione del DG1 codificata in base 64

Di seguito le firme dei metodi di cui sopra:

    -(void) setDG1B64:(NSString *) dg1B64;
    -(NSString *) getDG1B64;
    -(void) deleteDG1B64;

 - *setDG2B64*: per salvare la stringa relativa al DG2 codificata in base
   64
 - *getDG2B64*: get della stringa relativa al DG2 codificata in base 64
 - *deleteDG2B64*: cancellazione del DG2 codificata in base 64

Di seguito le firme dei metodi di cui sopra:

    -(void) setDG2B64:(NSString *) dg2B64;
    -(NSString *) getDG2B64;
    -(void) deleteDG2B64;

 - *setDG11B64*: per salvare la stringa relativa al DG11 codificata in
   base 64
 - *getDG11B64*: get della stringa relativa al DG11 codificata in base 64
 - *deleteDG11B64*: cancellazione del DG11 codificata in base 64

Di seguito le firme dei metodi di cui sopra:

    -(void) setDG11B64:(NSString *) dg11B64;
    -(NSString *) getDG11B64;
    -(void) deleteDG11B64;

 - *setDG12B64*: per salvare la stringa relativa al DG12 codificata in
   base 64
 - *getDG12B64*: get della stringa relativa al DG12 codificata in base 64
 - *deleteDG12B64*: cancellazione del DG12 codificata in base 64

Di seguito le firme dei metodi di cui sopra:

    -(void) setDG12B64:(NSString *) dg12B64;
    -(NSString *) getDG12B64;
    -(void) deleteDG12B64;

 - *setSODB64*: per salvare la stringa relativa al SODB codificata in base
   64
 - *getSODB64*: get della stringa relativa al SODB codificata in base 64
 - *deleteSODB64*: cancellazione del SODB codificata in base 64

Di seguito le firme dei metodi di cui sopra:

    -(void) setSODB64:(NSString *) sodB64;
    -(NSString *) getSODB64;
    -(void) deleteSODB64;

Nel caso specifico di lettura dati dal chip di una carta d’identità elettronico avvenuta tramite l’uso del PIN utente, la classe `PIMRTDDataHelper` mette a disposizione i seguenti metodi per la gestione della persistenza delle strutture dati derivanti da tale funzionalità:

 - *setCIEB64CertificateX509*: per salvare la stringa relativa al
   certificato X509 codificata in base 64, letto dal chip,
 - *getCIEB64CertificateX509*: get della stringa relativa al certificato X509 codificata in base 64,
 - *deleteCIEB64CertificateX509*: cancellazione della suddetta stringa.

Di seguito le firme dei metodi sopra elencati:

    -(void) setCIEB64CertificateX509:(NSString *) CIEb64CIEX509Certificate;
    -(NSString *) getCIEB64CertificateX509;
    -(void) deleteCIEB64CertificateX509;

 - *setCIEClearTextToSign*: per salvare la stringa relativa al testo in chiaro da firmare con il certificato X509,
 - *getCIEB64CertificateX509*: get della stringa relativa al testo in chiaro da firmare con il certificato X509,
 - *deleteCIEB64CertificateX509*: cancellazione della suddetta stringa

Di seguito le firme dei metodi sopra elencati:

    -(void) setCIEClearTextToSign:(NSString *) cieClearTextToSign;
    -(NSString *) getCIEClearTextToSign;
    -(void) deleteCIEClearTextToSign;

 - *setCIECertificateSignedChallenge*: per salvare la stringa relativa alla firma digitale codificata in base 64,
 - *getCIEB64CertificateX509*: get della stringa relativa alla firma digitale codificata in base 64,
 - *deleteCIEB64CertificateX509*: cancellazione della suddetta stringa

Di seguito le firme dei metodi sopra elencati:

	
    -(void) setCIECertificateSignedChallenge:(NSString *) cieCertSignedChallenge;
    -(NSString *) getCIECertificateSignedChallenge;
    -(void) deleteCIECertificateSignedChallenge;


 <div id='title6'/>
 
### Gestione dei dati relativi all'anagrafica
La classe `PIMRTDDataHelper` espone anche metodi per gestire la persistenza dei dati relativi al nome, al cognome e al codice fiscale dell’utente. Tali dati sono raccolti all’interno di un’unica classe `PIAnagraficaModel`. Tale classe può essere istanziata  tramite il seguente metodo:

    -(instancetype) initWithName:(nonnull NSString *)name surname:(nonnull NSString *)surname fiscalCode:(nonnull NSString*)fiscalCode

dove i parametri sono:

 - *name*: di tipo NSString, contiene il nome dell’utente
 - *surname*: di ripo NSString, contiene il cognome dell’utente
 - *fiscalCode*: di tipo NSString, contiene il codice fiscale dell’utente

la classe `PIMRTDDataHelper` mette a disposizione i seguenti metodi per la gestione della persistenza di questa struttura dati:

 - *addPIAnagrafica*: per salvare in persistenza la struttura dati
   PIAnagraficaModel,
 - *getPIAnagrafica*: get recuperare l’istanza di PIAnagraficaModel precedentemente salvata in persistenza,
 - *deleteAnagrafica*: cancellazione della suddetta istanza.

Di seguito le firme dei metodi sopra elencati:

    -(void) addPIAnagrafica:(PIAnagraficaModel*)anagrafica;
    -(PIAnagraficaModel*) getPIAnagrafica;
    -(void) deleteAnagrafica;


 <div id='title7'/>
 
### Gestione dei dati relativi a MRZ, tipo di documento elettronico, accessToken

La classe `PIMRTDDataHelper` espone anche metodi per gestire la persistenza dei dati relativi all’MRZ, alla tipologia di documento elettronico, all’accessToken.

Per l’MRZ sono definiti i seguenti metodi:

 - *setMRZ*: per salvare la stringa relativa all’MRZ
 - *getMRZ*: get della stringa relativa all’MRZ
 - *deleteMRZ*: cancellazione dell’MRZ

Di seguito le firme dei metodi di cui sopra:

    -(void) setMRZ:(NSString *) mrz;
    -(NSString *) getMRZ;
    -(void) deleteMRZ;

La tipologia di documento elettronico viene rappresentata come una stringa. Indica il tipo di documento, ma anche l'utilizzo nell'ambito del processo di identificazione dell'utente. Può pertanto assumere i seguenti valori:

 - “*ci*” per la carta d’identità cartacea,
 - “*cie*” per la carta d’identità elettronica con lettura dei dati del chip senza uso del PIN,
 - “*cie-pin*" per la carta d’identità elettronica con lettura dei dati del chip  tramite l’uso del PIN,
 - “*pe*” per il passaporto elettronico con lettura dei dati nel chip,
 - “*pe-cart*” per il passaporto elettronico senza lettura dei dati nel chip (come ad es. nel flusso di riconoscimento con bonifico nell'app PosteID)
 - “*cie-cart*” per la carte d'identità elettronica senza lettura dei dati nel chip (come ad es. nel flusso di riconoscimento con bonifico nell'app PosteID)

Per la gestione di questo dato la classe `PIMRTDDataHelper`  mette a disposizione i seguenti metodi:

 - *setDocType*: per salvare la stringa che identifica il tipo di
   documento
 - *getDocType*: get della stringa che identifica il tipo di documento
 - *deleteDocType*: cancellazione del tipo di documento

Di seguito le firme dei metodi di cui sopra:

    -(void) setDocType:(NSString *) docType;
    -(NSString *) getDocType;
    -(void) deleteDocType;

Infine per l’accessToken, restituito dal servizio di upload EID, sono definiti i seguenti metodi:

 - *setAccessToken*: per salvare la stringa relativa all’accessToken
 - *getAccessToken*: get della stringa relativa all’accessToken
 - *deleteAccessToken*: cancellazione della stringa relativa
   all’accessToken

Di seguito le firme dei metodi di cui sopra:

    -(void) setAccessToken:(NSString *) accessToken;
    -(NSString *) getAccessToken;
    -(void) deleteAccessToken;

 <div id='title8'/>
 
### Gestione persistenza generale 

 - deleteAllData: cancella TUTTE le strutture dati memorizzate in persistenza sulla libreria, tranne quelle relative al flusso di lettura della carta d’identità elettronica tramite PIN. Più precisamente questo metodo rimuove tutti gli oggetti di tipo PIImageMatch, di tipo PIImage, le strutture dati relative al contenuto del chip del documento elettronico (DG1, DG2, DG11, DG12, SODB), accessToken e docType  deleteCiePinData: cancella tutte le strutture dati memorizzate in persistenza relative al flusso di lettura della carta d’identità elettronica tramite PIN.

 <div id='title9'/>
 
## GESTIONE DATI NON PERSISTENTI
La classe `PIMRTDDataHelper` espone inoltre le seguenti properties da settare durante il ciclo di vita dell’App: 

 - *eidPubKeyB64*: la chiave pubblica codificata in base 64 del BE jod-electroinc-id, necessaria per l’upload dei dati verso lo stesso
 - *eidAzCodeB64*: l’azCode codificata in base 64 da passare al BE jod-electroinc-id per autorizzare l’upload

**N.B**. per questi attributi non viene gestita alcuna persistenza. 

 <div id='title10'/>
 
## METODI DI UTILITY
La classe `PIMRTDDataHelper` espone il seguente metodo di utility:

     -(NSString *) getCodeAppChallenge;

L’ invocazione di questo metodo da parte del codice applicativo è un passo propedeutico all’upload dei dati verso il servizio EID.  Infatti contestualmente alla generazione del *codeChallenge* viene generato internamente al framework anche un parametro *codeVerify*, strettamente legato al *codeChallenge*. Il valore di questo parametro verrà utilizzato nella chiamata http per l’upload dei dati.

Da notare che ogni richiesta di generazione di un *codeChallenge* comporta la generazione di un nuovo valore di *codeVerify*. Inoltre tali dati non sono soggetti a persistenza nel framework.
