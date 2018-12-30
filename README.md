# synexts
Debugger (WinDbg/DbgEng) extension DLL: create artificial symbols and artificial modules in debug engine's module list.

## How to install/use
TBD

## Exported extensions
* !synexts.help - print help message
* !synexts.addsymbol \<NAME\> \<OFFSET\> \<SIZE\> - create artificial symbol in any existing module
* !synexts.addmodule \<NAME\> \<PATH\> \<BASE\> \<SIZE\> - create artificial module in engine's module list

## Debug engine API references
 * [IDebugSymbols3::AddSyntheticSymbol](https://docs.microsoft.com/windows-hardware/drivers/ddi/content/dbgeng/nf-dbgeng-idebugsymbols3-addsyntheticsymbol)
 * [IDebugSymbols3::AddSyntheticModule](https://docs.microsoft.com/windows-hardware/drivers/ddi/content/dbgeng/nf-dbgeng-idebugsymbols3-addsyntheticmodule)
