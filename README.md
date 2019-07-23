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
- `outFile` *(optional)* describes the output file, which its members `filePath` signify the csv file path and `defaultAppend` determines if the default action is to append the existing file. `writeConfirm` determines if write confirmation has to be done.
- `presetLists` is an array of objects consisting of `account type` and `category list`
- `type` is the type of account/transaction. Can be any value, but recommended values are `Account`, `Expense`, `Income`. You must have at least one category and child for each type.
- `cat` is the main category
- `child` is the child category 


## Creating the json file
### Manual Creation
#### json v2.0
As of version 2.0, the json file will be unified for a single format that encompasses simple and advanced file type. It also has sections for backlogging support. 
This is a sample file for a the json configuration. `a`(or, `account`) must be the first object in the `presetLists` array.

```
{
    "outFile":[
    {
        "advFormat" : true / false,
        "filePath" : "<Your csv file path>",
        "defaultAppend" : true / false,
        "writeConfirm" : true
    }
    ],
    "presetLists":[
        {    
            "type" : "a",
            "catList" : [
                {
                    "cat" : "Category1",
                    "child" : [
                        "Child1.1",
                        "Child1.2"
                    ]
                }
            ]
        },
        {
            "type" : "e / i",
            "catList" : [
                {
                    "cat" : "Category2",
                    "child" : [
                        "Child2.1",
                        "Child2.2"
                    ]
                }
            ]
    ]
}
```
You may also refer to "./Tests/ktn.json" for a real life sample file.

#### (Future) Advanced json
To be announced, depending on project popularity.

#### (Future) Prompted json file creation
Depending the popularity of this project, a tool may be created to facilitate this use case. You are always welcome to fork my project.

## Specifying default path
If you are compiling yourself, you may edit in your default path that you use to store your json and csv file so that you are not required to manual key in every time:
- In ".\BlueCoinsImportTool.h", you edit the following variable:
```
const string defaultJsonFileName = "<Your path>";
```
- Take note that you need to add extra backslashes for directory paths, e.g.:
``` D:\Bluecoins-ImportTool\Tests\ktn.json ``` would be ``` D:\\Bluecoins-ImportTool\\Tests\\ktn.json ```

## Split Transaction Support
Starting from v1.3, there will be suppot for split transactions. Just toggle option no. 6 at the main menu. You will see an extra section of text when the option is toggled to "true".
- Do take note that for split transactions to work, the following need to be the same. Future versions of the program will add functionality to lock in required lock-in : 
  - Transaction Type
  - Title
  - Date, Time
- Using different label sets or status for each split is not currently supported. Only those from the first row will be used for each split transaction

## No support / not tested
- Compilers other than the one default in Visual Studio 2019
- CMake. Not tried yet.

## Project Milestones
- 23 July 2019, v1.3 released
- 5 July 2019, v1.2 released
- 1 July 2019, v1.1 released
- 27 June 2019, Project announcement to the BlueCoins Community
- 26 June 2019, Transfers logic completed
- 24 June 2019, Overall completed
- 21 June 2019, json file standard decided
- 16 June 2019, Project Started

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
