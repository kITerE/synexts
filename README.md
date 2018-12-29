# synexts
Debugger (WinDbg/DbgEng) extension DLL: create artificial symbols and artificial modules in debug engine's module list.

## How to install/use
TBD

## Exported extensions
* help - print help message
* addsymbol \<NAME\> \<OFFSET\> \<SIZE\> - create artificial symbol in any existing module
* addmodule \<NAME\> \<PATH\> \<BASE\> \<SIZE\> - Create artificial symbol in any existing module

## Debug engine API references
 * [IDebugSymbols3::AddSyntheticSymbol](https://docs.microsoft.com/windows-hardware/drivers/ddi/content/dbgeng/nf-dbgeng-idebugsymbols3-addsyntheticsymbol)
 * [IDebugSymbols3::AddSyntheticModule](https://docs.microsoft.com/windows-hardware/drivers/ddi/content/dbgeng/nf-dbgeng-idebugsymbols3-addsyntheticmodule)
