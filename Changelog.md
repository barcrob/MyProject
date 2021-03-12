#### 2.2.4 - March 12, 2021
* Added settings in podspec for arm64 architecture strip on simulator, required for XCode 12 release


#### 2.2.0 - March 30, 2019
* Added `minimumCharacterHeight` property to enable SwiftyTesseract to ignore characters below
a user-defined threshold.
* Added `createPDF(from:)` method to create a PDF `Data` object from an array of `UIImage`s that
OCR is performed on. 

#### 2.1.0 - February 2, 2019
* Added `preserveInterwordSpaces` property to allow more than one space between words if desired.
* Updated underlying Tesseract library to 4.0.0 release version.

#### 2.0.0 - September 25, 2018
* `CustomData` was enum removed in favor of keeping one enum, `RecognitionLanguage`, that utilizes an associated types as opposed to raw values. This is the only breaking change in 2.0.0 that should only affect users of `CustomData`.
* The underlying Tesseract library has been updated to 4.0.0-beta.4

#### 1.1.0 - May 5, 2018
* Created `CustomData` enum to enable the use of custom `.traineddata` files.
* Added support for iOS 9.0

#### 1.0.3 - April 4, 2018
* Added semaphore to make `performOCR(on:completionHandler:)` thread-safe

#### 1.0.2 - April 2, 2018
* Fixed documentation

#### 1.0.1 - March 30, 2018

* Fixed issue with disk I/O bug that starting occurring in iOS 11.3 that caused a crash when calling `write(to:options:)` on an instance of `Data` to a file name that didn't exist (previously the file would be created if it didn't exist). All conversions from UIImage to Pix are now done in memory, completely bypassing disk I/O altogether.
