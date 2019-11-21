// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#import "../COM/KG_GetKeyInfo_FJRS.ocx" no_namespace
// CDKG_GetKeyInfo_FJRS 包装类

class CDKG_GetKeyInfo_FJRS : public COleDispatchDriver
{
public:
	CDKG_GetKeyInfo_FJRS(){} // 调用 COleDispatchDriver 默认构造函数
	CDKG_GetKeyInfo_FJRS(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDKG_GetKeyInfo_FJRS(const CDKG_GetKeyInfo_FJRS& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _DKG_GetKeyInfo_FJRS 方法
public:
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString KGGetKeyInfo()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}

	// _DKG_GetKeyInfo_FJRS 属性
public:

};
