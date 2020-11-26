


## Funzionalità del framework
Le funzionalità del framework si possono dividere in 3 macro categorie:

 
 - utilizzo della facility di acquisizione della foto utente
          (selfie), scansione della banda MRZ del documento tramite
          tecnologia OCR, lettura del chip del documento elettronico
          tramite tecnologia NFC e registrazione di un video. Il risultato
          di queste funzionalità sono file immagini e video salvati
          all’interno della cartella Documents del dispositivo e strutture
          dati relative alle informazioni contenute nel documento
          elettronico



 - gestione della persistenza dei file e delle relative strutture dati:
   tramite il componente PIMRTDDataHelper è possibile salvare le
   strutture dati relative alle foto e alle informazioni lette dal documento elettronico. La gestione dei dati salvati e la loro
   consistenza è demandata all’App che dovrà pulire la persistenza
   all’occorrenza e in base al contesto progettuale mediante il
   componente PIMRTDDataHelper.
   
 - upload dei dati verso il BE jod-electronic-id: alla fine del flusso
   di acquisizione dati sarà possibile utilizzare il framework per
   eseguire un upload di tali dati verso il BE jod-electronic-id. E’
   demandato all’App la scelta del momento di invio dei dati verso il
   BE.
   
[Facility di Acquisizione Foto, Video e Dati](FacilityAcquisizioneFotoVideoDati.md)

[Gestione della Persistenza](GestionePersistenza.md)

[Upload dei dati](uploadDati.md)



