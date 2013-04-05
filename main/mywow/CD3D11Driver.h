#pragma once

#include "base.h"
#include "IVideoDriver.h"
#include <map>
#include <list>

class CD3D11SceneStateServices;
class CD3D11ShaderServices;
class CD3D11MaterialRenderServices;
class CD3D11VertexDeclaration;
class IVertexShader;

class CD3D11Driver : public IVideoDriver
{
public:
	CD3D11Driver();
	virtual ~CD3D11Driver();

public:
	bool initDriver(HWND hwnd, u32 adapter, bool fullscreen, bool vsync, u8 antialias, bool multithread);

public:
	virtual E_DRIVER_TYPE getDriverType() const { return EDT_DIRECT3D11; }
	virtual u32 getAdapterCount() const { return AdapterCount; }

	virtual bool beginScene();
	virtual bool endScene();
	virtual bool clear(bool renderTarget, bool zBuffer, bool stencil, SColor color);

	virtual bool queryFeature(E_VIDEO_DRIVER_FEATURE feature) const;

	virtual void setTransform( E_TRANSFORMATION_STATE state, const matrix4& mat );
	virtual const matrix4& getTransform( E_TRANSFORMATION_STATE state ) const { return CurrentDeviceState.matrices[state]; }

	virtual void setMaterial(const SMaterial& material);
	virtual const SMaterial& getMaterial() const { return Material; }
	virtual SOverrideMaterial& getOverrideMaterial() { return OverrideMaterial; }

	virtual void setTexture(u32 stage, ITexture* texture);
	virtual ITexture* getTexture(u32 index) const;

	virtual bool setRenderTarget( IRenderTarget* texture );

	virtual void setViewPort( recti area );
	virtual const recti& getViewPort() const { return Viewport; }

	virtual void registerLostReset( ILostResetCallback* callback );
	virtual void removeLostReset( ILostResetCallback* callback );

	virtual void setDisplayMode(const dimension2du& size);
	virtual dimension2du getDisplayMode() const;
	virtual bool setDriverSetting(const SDriverSetting& setting);
	virtual const SDriverSetting& getDriverSetting() const { return DriverSetting; }

	virtual ISceneStateServices* getSceneStateServices() const;
	virtual IMaterialRenderServices* getMaterialRenderServices() const;
	virtual IShaderServices*	getShaderServices() const;

	//draw
	virtual void draw3DMode( const SBufferParam& bufferParam, 
		E_PRIMITIVE_TYPE primType,
		u32 primCount, 
		const SDrawParam& drawParam);

	virtual void draw2DMode( const SBufferParam& bufferParam, 
		E_PRIMITIVE_TYPE primType,
		u32 primCount, 
		const SDrawParam& drawParam,
		const S2DBlendParam& blendParam);

	virtual void drawDebugInfo(const c8* strMsg);

private:
	void drawIndexedPrimitive( const SBufferParam& bufferParam, IVertexShader* vs, 
		E_PRIMITIVE_TYPE primType,
		u32 primCount, 
		const SDrawParam& drawParam);
	void drawPrimitive( const SBufferParam& bufferParam, IVertexShader* vs, 
		E_PRIMITIVE_TYPE primType,
		u32 primCount,
		const SDrawParam& drawParam);


	void recreateDepthStencilView(dimension2du size, u32 antialias, u32 quality);
	bool reset(bool recreateSwapChain);
	void createVertexDecl();
	void releaseVertexDecl();
	CD3D11VertexDeclaration* getVertexDeclaration(E_VERTEX_TYPE type);
	void setVertexDeclaration(E_VERTEX_TYPE type, IVertexShader* vs);
	void setRenderState3DMode(E_VERTEX_TYPE vType);
	void setRenderState2DMode(E_VERTEX_TYPE vType, const S2DBlendParam& blendParam );
	void logCaps();

public:
	HMODULE		HLibDXGI;
	HMODULE		HLibD3D;
	// DXGI objects
	DXGI_SWAP_CHAIN_DESC Present;
	IDXGISwapChain* SwapChain;
	IDXGIAdapter* Adapter;
	IDXGIOutput* DXGIOutput;
	IDXGIFactory* DXGIFactory;

	//D3D 11 Device Objects
	D3D_FEATURE_LEVEL		FeatureLevel;
	ID3D11Device*		pID3DDevice11;
	ID3D11DeviceContext*	ImmediateContext;

	// Back and depth buffers
	ID3D11RenderTargetView* DefaultBackBuffer;
	ID3D11Texture2D*		DefaultDepthTexture;
	ID3D11DepthStencilView* DefaultDepthBuffer;
	DXGI_FORMAT		BackBufferFormat;
	DXGI_FORMAT		DepthStencilFormat;	

	//rendertarget
	IRenderTarget*		CurrentRenderTarget;

	//device settings
	HWND		HWnd;
	D3D_DRIVER_TYPE	DevType;

	CAdapterInfo	AdapterInfo;
	SDriverSetting	DriverSetting;

	CRITICAL_SECTION	cs;

private:
	struct SDeviceState				//除去material以外的state，material设置时已经做了cache
	{
		void reset()
		{
			vType = (E_VERTEX_TYPE)-1;
			vBuffer0= vBuffer1 = NULL;
			iBuffer = NULL;
			vOffset0 = vOffset1 = 0;
			memset(matrices, 0, sizeof(matrices));
		}

		E_VERTEX_TYPE 	vType;
		IVertexBuffer*	vBuffer0;
		IVertexBuffer	*vBuffer1;

		u32		vOffset0;
		u32		vOffset1;

		IIndexBuffer*		iBuffer;
		matrix4		matrices[ETS_COUNT];
	};

private:
	SMaterial	Material, LastMaterial;
	SOverrideMaterial		OverrideMaterial;
	//2D
	SMaterial	InitMaterial2D;
	SOverrideMaterial		InitOverrideMaterial2D;

	recti		Viewport;
	dimension2du	ScreenSize;
	u32		AdapterCount;
	u32		PrimitivesDrawn;
	u32		DrawCall;

	// device state cache
	SDeviceState	CurrentDeviceState;
	IMaterialRenderer*		MaterialRenderer;
	CD3D11SceneStateServices*	SceneStateServices;
	CD3D11ShaderServices*	ShaderServices;
	CD3D11MaterialRenderServices*		MaterialRenderServices;

	E_RENDER_MODE		CurrentRenderMode;
	bool		ResetRenderStates;

	CD3D11VertexDeclaration* VertexDeclarations[EVT_COUNT];

	typedef std::list<ILostResetCallback*, qzone_allocator<ILostResetCallback*>> T_LostResetList;
	T_LostResetList	LostResetList;

	c8		DebugMsg[512];

	friend class CD3D11MaterialRenderServices;
};



