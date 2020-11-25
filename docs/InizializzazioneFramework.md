

## Inizializzazione framework
E' necessario inizializzare il framework attraverso il metodo `initLibraryWithInitConfig` della classe `PIMRTDDataHelper`, il metodo accetta in input l'oggetto `PIInitConfig` sul quale vanno configurate le seguenti proprietà: 

 - *baseURL*: base url del BE jod-electronic-id
 - *skipSSL*: true se in collaudo, false in produzione

**NOTA**: il metodo `initLibraryWithInitConfig` deve esser richiamato all'inizio del ciclo di vita dell'App (esempio AppDelegate, splash screen, ecc..). 

**Esempio di inizializzazione:**

    PIInitConfig *config = [[PIInitConfig alloc]initWithBaseURL:@"BASE_URL_BE" skipSSL:false];
    [[PIMRTDDataHelper shareInstance] initLibraryWithInitConfig:config];

