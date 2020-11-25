

## Procedura per l'installazione

Per l'installare il framework all'interno di un progetto tramite Cocoapods occorre:

 1. aggiungere in cima al Podfile la riga *source
    'http://192.168.116.5:3000/mobileteam/posteitaliane-privatespecs-repo.git',*
    prima di quella relativa al repository Cocoapods. Se quest'ultima
    non è inserita, aggiungerla.
 3. aggiungere al Podfile la dipendenza, inserendo la riga pod
    ‘posteMRTDiOS-iphoneos' per installare la versione ottimizzata per
    device, oppure la riga  pod ‘posteMRTDiOS-iphonesimulator’ per la
    versione relativa al simulatore.
 4. lanciare il comando pod install

Di seguito esempio di Podfile: 

                source 'http://192.168.116.5:3000/mobileteam/posteitaliane-privatespecs-repo.git'
                source 'https://github.com/CocoaPods/Specs.git' #Se non inserita, aggiungerla

                platform :ios, '9.0'	
                use_frameworks!
                    
                target 'APP-X_Y_Z' do
                    
	                pod 'posteMRTDiOS-iphoneos'
                end
                    
                target 'APP-X_Y_ZTests' do
                    
	                inherit! :search_paths
                    
                end

