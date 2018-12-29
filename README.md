# synexts
Debugger (WinDbg/DbgEng) extension DLL: create artificial symbols and artificial modules in debug engine's module list.

## How to install/use
TBD

## Exported extensions
* help
Print help message
* addsymbol <NAME> <OFFSET> <SIZE>
Create artificial symbol in any existing module
* addmodule <NAME> <PATH> <BASE> <SIZE>
Create artificial symbol in any existing module

## Debug engine API references
 * [IDebugSymbols3::AddSyntheticSymbol]()
 * [IDebugSymbols3::AddSyntheticModule]()
