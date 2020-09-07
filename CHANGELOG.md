# Bluecoins Import Tool Changelog

## v2.0

- Updated the nlohmann::json library
- Streamlined code and internal data format for better readibility and expandability.
- Streamlined displaying of information
- Fixed bug where file does not properly open/write/create when re-defining CSV outputs within tool.
- Changed JSON format to be more future-proof.
- Added feature / squashed bug where incorrect data formats will hang the whole tool.
- Added feature to allow "undo" action for non-locked previous fields.
- Added feature to lock fields during input. Such that, users can opt to not re-key in similar fields for transactions.
- Added better bug catching functionality, such that, errors will be thrown and catched instead of just throwing errors.
- Added split transaction locking for fields that require so automatically.
- Added function for JSON writeback to origin file. This serves as a base for upcoming interactive account input feature.
- Added function for "existing" and "target" account balance. Alert will also be displayed if "targetBal" is defined in JSON.

## v1.3

- Fixed bug where program will exit when defautAppend has bool value.

## v1.2

- Added function to introduce output path defined within JSON file.
- Added more documentation information.

## v1.1

- Fixed bug where reset does not reset transfer fields.

## v1.0

- Initial release.
- Feature to add entries (expense, income, transfers) interactively according to BlueCoins CSV format.