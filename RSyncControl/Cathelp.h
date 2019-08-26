#include "comcat.h"

// Helper function to create a component category and associated
// description
extern HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);

// Helper function to register a CLSID as belonging to a component
// category
extern HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

// HRESULT UnRegisterCLSIDInCategory - Remove entries from the registry 
extern HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
