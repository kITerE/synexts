// synexts.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

// ----------------------------------------------------------------------------

namespace
{

// ----------------------------------------------------------------------------

const CHAR g_szArgumentTokens[] = " \t";

// ----------------------------------------------------------------------------

}

// ----------------------------------------------------------------------------

extern "C"
HRESULT
CALLBACK
help(
    __in IDebugClient4 *pDebugClient,
    __in PCSTR args
)
{
    UNREFERENCED_PARAMETER(args);

    // query required debug engine interface
    ATL::CComQIPtr<IDebugControl> pDebugControl{pDebugClient};

    // print help messafe
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "Synthetic symbols extension\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "    addsymbol   <NAME> <OFFSET> <SIZE>\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "                create artificial symbol in any existing module\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "    addmodule   <NAME> <PATH> <BASE> <SIZE>\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "                create artificial loaded modules in engine's module list\n");
    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "\n");

    return S_OK;
}

// ----------------------------------------------------------------------------

extern "C"
HRESULT
CALLBACK
addsymbol(
    __in IDebugClient4 *pDebugClient,
    __in PCSTR args
)
{
    // query required debug engine interfaces
    ATL::CComQIPtr<IDebugControl> pDebugControl{pDebugClient};
    ATL::CComQIPtr<IDebugSymbols3> pDebugSymbols{pDebugClient};

    // parse command arguments
    const ATL::CStringA csArguments{args};

    int nTokenize{};
    const auto csName{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csName.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing first parameter (NAME)\n");
        return E_INVALIDARG;
    }

    const auto csOffset{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csOffset.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing second parameter (OFFSET)\n");
        return E_INVALIDARG;
    }

    DEBUG_VALUE OffsetValue{};
    auto hResult = 
        pDebugControl->Evaluate(
            csOffset,
            DEBUG_VALUE_INVALID,
            &OffsetValue,
            nullptr);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Second parameter (OFFSET) cannot be converted to number (0x%x)\n", hResult);
        return hResult;
    }

    const auto csSize{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csSize.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing third parameter (SIZE)\n");
        return E_INVALIDARG;
    }

    DEBUG_VALUE SizeValue{};
    hResult =
        pDebugControl->Evaluate(
            csSize,
            DEBUG_VALUE_INVALID,
            &SizeValue,
            nullptr);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Third parameter (SIZE) cannot be converted to number (0x%x)\n", hResult);
        return hResult;
    }

    // try to create artificial symbol
    hResult =
        pDebugSymbols->AddSyntheticSymbol(
            OffsetValue.I64,
            SizeValue.I32,
            csName,
            DEBUG_ADDSYNTHSYM_DEFAULT,
            nullptr);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Cannot add synthetic symbol (0x%x)\n", hResult);
        return hResult;
    }

    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "Synthetic symbol successfully added\n");
    return S_OK;
}

// ----------------------------------------------------------------------------

extern "C"
HRESULT
CALLBACK
addmodule(
    __in IDebugClient4 *pDebugClient,
    __in PCSTR args
)
{
    // query required debug engine interfaces
    ATL::CComQIPtr<IDebugControl> pDebugControl{pDebugClient};
    ATL::CComQIPtr<IDebugSymbols3> pDebugSymbols{pDebugClient};

    // parse command arguments
    const ATL::CStringA csArguments{args};

    int nTokenize{};
    const auto csName{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csName.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing 1st parameter (NAME)\n");
        return E_INVALIDARG;
    }

    const auto csPath{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csPath.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing 2th parameter (PATH)\n");
        return E_INVALIDARG;
    }

    const auto csBase{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csBase.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing 3th parameter (BASE)\n");
        return E_INVALIDARG;
    }

    DEBUG_VALUE BaseValue{};
    auto hResult = 
        pDebugControl->Evaluate(
            csBase,
            DEBUG_VALUE_INVALID,
            &BaseValue,
            nullptr);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "BASE (3th parameter) cannot be converted to number (0x%x)\n", hResult);
        return hResult;
    }

    const auto csSize{csArguments.Tokenize(g_szArgumentTokens, nTokenize)};
    if (csSize.IsEmpty())
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Missing 4th parameter (SIZE)\n");
        return E_INVALIDARG;
    }

    DEBUG_VALUE SizeValue{};
    hResult =
        pDebugControl->Evaluate(
            csSize,
            DEBUG_VALUE_INVALID,
            &SizeValue,
            nullptr);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "SIZE (4th) cannot be converted to number (0x%x)\n", hResult);
        return hResult;
    }

    // try to create artificial loaded module
    hResult =
        pDebugSymbols->AddSyntheticModule(
            BaseValue.I64,
            SizeValue.I32,
            csPath,
            csName,
            DEBUG_ADDSYNTHMOD_DEFAULT);
    if (S_OK != hResult)
    {
        pDebugControl->Output(DEBUG_OUTPUT_ERROR, "Cannot add synthetic module (0x%x)\n", hResult);
        return hResult;
    }

    pDebugControl->Output(DEBUG_OUTPUT_NORMAL, "Synthetic module successfully added\n");
    return S_OK;
}

// ----------------------------------------------------------------------------
