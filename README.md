# Bluecoins Import Tool

[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/kwongtn/Bluecoins-ImportTool/issues)
[![HitCount](http://hits.dwyl.io/kwongtn/Bluecoins-ImportTool.svg)](http://hits.dwyl.io/kwongtn/Bluecoins-ImportTool)

[![Coverage Status](https://coveralls.io/repos/github/kwongtn/Bluecoins-ImportTool/badge.svg?branch=master)](https://coveralls.io/github/kwongtn/Bluecoins-ImportTool?branch=master)

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/kwongtn/Bluecoins-ImportTool/LICENSE.MIT)
[![GitHub Releases](https://img.shields.io/github/release/kwongtn/Bluecoins-ImportTool.svg)](https://github.com/kwongtn/Bluecoins-ImportTool/releases)

[![GitHub Issues](https://img.shields.io/github/issues/kwongtn/Bluecoins-ImportTool.svg)](http://github.com/kwongtn/Bluecoins-ImportTool/issues)

[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/kwongtn/Bluecoins-ImportTool.svg)](http://isitmaintained.com/project/kwongtn/Bluecoins-ImportTool "Average time to resolve an issue")
[![Percentage of issues still open](http://isitmaintained.com/badge/open/kwongtn/Bluecoins-ImportTool.svg)](http://isitmaintained.com/project/kwongtn/Bluecoins-ImportTool "Percentage of issues still open")


## Introduction
This is a little tool created for the import of transactions for the Bluecoins app.  
As I am a lazy person, I would frequently gather a lot of receipts and do it in one go. Typing at phones proves to be a strain when there is a load.  
Therefore, this tool is created.
According to the prompts, you can input and select accounts' number as required, speeding up the input process.
The inputted file will then be exported to a csv file that can be imported into the bluecoins app.

*Note: There is no support for advanced file type yet. You are welcome to fork this repo and add functionality.

Released by KwongTN under the MIT license. Contains code from https://github.com/nlohmann/json .

For the bluecoins import guide, refer to:
http://www.bluecoinsapp.com/import-guide/


## json file terminology
- `jsonType` simply means the type of the json file, there are `simple` and `advanced`. For more details refer to the [bluecoins import guide](http://www.bluecoinsapp.com/import-guide/).
- `outFile` (optional) describes the output file, where its members :
  - `filePath` signify the csv file path 
  - `defaultAppend` determines if the default action is to append the existing file.
  - `noConfirmation` determines if we commit to csv writing without asking for confirmation.
  - `writebackChanges` determines if we want to update `bluecoinsBal` after each transaction is done. This is a destructive operation that overwrites the file if everything in memory.
  - `writebackJSONSpacing` determines the spacing when we writeback the JSON file.
- `presetLists` is an array of objects consisting of `account type` and `category list`
- `type` is the type of account/transaction. Can be any value, but recommended values are `Account`, `Expense`, `Income`. You must have at least one category and child for each type. The first element in the `presetLists` array must be describing account.
- `cat` describes the main category (E.g. `Bank` (For accounts), `Car` (For expenses) etc.)
- `child` is the child category, where more details are described:
  - `childName` is the name of the child category (E.g. `Savings Account` (For accounts -> Bank), `Fuel` (For expenses -> Car))
  - `currency` not used for this version, but is placed in for compatibility with future "advanced" CSV file creation.
  -  `bluecoinsBal` is a reference to the existing balance in the BlueCoins app. You are recommended to update this before inputting any entries. New entries will be deducted/added towards this value if `writebackChanges` is enabled.
  - `targetBal` is to provide a check, to see if the inputs have hit the target balance. Useful for people that do lots of backlog entries.

### Data Dictionary  
Added this section cause I've learnt in uni and cause it would be easier for you to know what went wrong in your configuration.

| Name/Key | Data Type | Optional? | Sample Input |
| --- | --- | --- | --- |
| jsonType | string | ✅ | "Simple" | 
| outFile | object | ✅ | {   } |
| outFile:defaultAppend | boolean | ✅ | true/false |
| outFile:filepath | string | ✅ | "D:\\PathName\\something.csv" |
| outFile:noConfirmation | boolean | ✅ | true/false |
| outFile:writebackChanges | boolean | ✅ | true/false |
| outFile:writebackJSONSpacing | integer | ✅ | 1, 2, 3... |
| presetLists | array | ❌ | [ { }, ... ] |
| presetLists[]type | string | ❌ | "Account", "Income", "Expense" |
| presetLists[]catList | array | ❌ | [ { }, ... ] |
| presetLists[]catList[]cat | string | ❌ | "Bank", "Cash"... |  
| presetLists[]catList[]child | array | ❌ | [ { }, ... ] |
| presetLists[]catList[]child[]bluecoinsBal | double | ✅ | 1000.00 |
| presetLists[]catList[]child[]childName | string | ❌ | "Savings Account" ... |
| presetLists[]catList[]child[]currency | string | ✅ | "MYR", "USD"... |
| presetLists[]catList[]child[]targetBal | double | ✅ | 1000.00 |


## Creating the json file
### Manual Creation
#### json v2.0
As of version 2.0, the json file will be unified for a single format that encompasses simple and advanced file type. It also has sections for backlogging support. 
This is a sample file for a the json configuration. `a`(or, `account`) must be the first object in the `presetLists` array.

```json
{
    "outFile":[
    {
        "defaultAppend": true / false,,
        "filePath": "<Your csv file path>"
        "noConfirmation": true / false,
        "writebackChanges": true / false,
        "writebackJSONSpacing": 4
    }
    ],
    "presetLists":[
        {    
            "type" : "a / e / i",
            "catList" : [
                {
                    "cat" : "Category1",
                    "child" : [
                        {
                            "childName" : "Child1.1",
                            "currency" : "MYR",
                            "bluecoinsBal" : 2000.00,
                            "targetBal": 1876.55
                        },{
                            "childName" : "Child1.2",
                            "currency" : "USD",
                            "bluecoinsBal" : 2000.00,
                            "targetBal" : 1000.00
                        }
                    ]
                }
            ]
        }
    ]
}
```
You may also refer to "./Tests/ktn.json" for a real life sample file.


## Specifying default path
If you are compiling yourself, you may edit in your default path that you use to store your json and csv file so that you are not required to manual key in every time:
- In ".\BlueCoinsImportTool.h", you edit the following variable:
```
const string defaultJsonFileName = "<Your path>";
```
- Take note that you need to add extra backslashes for directory paths, e.g.:
``` D:\Bluecoins-ImportTool\Tests\ktn.json ``` would be ``` D:\\Bluecoins-ImportTool\\Tests\\ktn.json ```

## Split Transaction Support
Starting from v1.3, there will be support for split transactions. Just toggle option no. 6 at the main menu. You will see an extra section of text when the option is toggled to "true".
- <strike>Do take note that for split transactions to work, the following need to be the same. Future versions of the program will add functionality to lock in required lock-in, namely Transaction Type, Title, Date, Time</strike> Functionality added in v2.0 .
- Using different title, label sets or status for each split is not currently supported. Only those from the first row will be used for each split transaction

## No support / not tested
- Compilers other than the one default in Visual Studio 2019
- CMake. Not tried yet.

## Project Milestones  

| Dates | Description |
| --- | --- |
| 7 September 2020 | v2.0 released |
| 26 August 2020 | Development for v2.0 resumed at branch "development" |
| 23 July 2019 | v1.3 released |
| 6 July 2019 | Development for v2.0 started at branch "development" |
| 5 July 2019 | v1.2 released |
| 1 July 2019 | v1.1 released |
| 27 June 2019 | Project announcement to the BlueCoins Community |
| 26 June 2019 | Transfers logic completed |
| 24 June 2019 | Overall completed |
| 21 June 2019 | json file standard decided |
| 16 June 2019 | Project Started |

## Known Issues
- "-1" to go back to previous fields does not work for locked fields. <strike>A little lazy to fix it cause it'll probably require much code rewriting. Aand I'm lazy.</strike> Probably will be fixed in v2.x .

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

This tool is licensed under the MIT License <http://opensource.org/licenses/MIT>.  
Copyright &copy; 2019 Kwong Tung Nan

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

* * *

This tool contains code from "json for modern C++" from Niels Lohmann which is licensed under the [MIT License](http://opensource.org/licenses/MIT) (see above).   
Copyright &copy; 2013-2019 [Niels Lohmann](http://nlohmann.me/) , <mail@nlohmann.me>


## Future functionality
### Backlog tool
Will be completed in the near future, json file will be future proofed for advanced json support.
The backlog tool will enable users to define current balance (balance as recorded in the bluecoins app) and actual balance (balance in the real world). As transactions are being input, the current balance will be updated accordingly in memory and in the json file. The goal is for the user to match both the current and actual balance.

### Placeholder support
Transaction creator to match current balance and actual balance.

### Softcode default json file location
Selecting "d" on the json file selection page will no longer be required to be hardcoded. Default path will be defined as ".\Bluecoins-Import.json".

### Defaulting file output location
If nothing is specified in the json file and user inputs "d", the file will be created at the current directory.

### Preset Titles & Templates
The user will be able to preset commonly used titles in the json file, and during runtime define templates for input.

### Advanced json support
To be announced, depending on project popularity.

### Prompted json file creation
Depending the popularity of this project, a tool may be created to facilitate this use case. You are always welcome to fork my project.

### Alert after targetBal and bluecoinsBal are the same  
To have another way of telling the user

### Option to stop userinput after targetBal and bluecoinsBal are the same  
Well... To prevent users from accidentally inputting more than the file can handle?