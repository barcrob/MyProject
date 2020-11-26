

## Acquisizione della foto del documento cartaceo

L’acquisizione della foto del documento cartaceo è demandata all’applicativo che può a tal fine utilizzare il controller del framework `PICameraViewController` (vedere più avanti per ulteriori dettagli). Una volta acquisita la foto, se si vuole che il framework la includa tra le altre risorse da inviare in upload al back-end, l’app dovrà settare sul singleton `PIMRTDDataHelper` il relativo oggetto `PIImage`. 

Nel caso di immagini ospitate sul cloud l’oggetto `PIImage` dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: `_URI`, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file immagine PRIMA del caricamento sul cloud
 - *file*: il link alla risorsa sul cloud

Nel caso di immagini per cui deve essere eseguito l’upload sul sistema di BE collegato alla libreria (jod-electroinc-id BE) l’oggetto PIImage dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: `_LOCAL`, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il path al file system restituito dal

Nel caso di immagini per cui deve essere eseguito l’upload sul sistema di BE di tipo AZURE l’oggetto PIImageMatch dovrà essere istanziato con i seguenti parametri: 

 - *ResourceType*: `_AZURE`, valore dell'enumerato `PIImageResourceType`
 - *Description*: stringa descrittiva del file, opzionale
 - *hash*: l’hash del file
 - *file*: il token azure

**Esempio** gestione di una foto del documento cartaceo da caricare su jod-electronic-id BE:

    -(void)someMethod{
       ...
       NSString *path = @"path al file dell'immagine sul file system";
       NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
       PIImage * docImage = [[PIImage alloc]initWithResourceType:_LOCAL description:@"Foto CI" hash:fileHash file:path];
       [[PIMRTDDataHelper sharedInstance]addDataCartPIImage:docImage];
       
       ...
    }

**Esempio** gestione di una foto del documento cartaceo caricata su cloud:

    -(void)someMethod{
        ...
        NSString *path = @"path al file dell'immagine sul file system";
        NSString * fileHash = [PIFileManager getHashSHA256FileAtPath:path];
        PIImage * docImage = [[PIImage alloc]initWithResourceType:_URI description:@"Foto CI" hash:fileHash file:@"https://link_a_una_risorsa_su_cloud"];
        [[PIMRTDDataHelper sharedInstance]addDataCartPIImage:docImage];
        ...
    }

