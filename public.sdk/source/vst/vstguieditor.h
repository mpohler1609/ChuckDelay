//------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.5.2
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/vstguieditor.h
// Created by  : Steinberg, 04/2005
// Description : VSTGUI Editor
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2012, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// This Software Development Kit may not be distributed in parts or its entirety  
// without prior written agreement by Steinberg Media Technologies GmbH. 
// This SDK must not be used to re-engineer or manipulate any technology used  
// in any Steinberg or Third-party application or software module, 
// unless permitted by law.
// Neither the name of the Steinberg Media Technologies nor the names of its
// contributors may be used to endorse or promote products derived from this 
// software without specific prior written permission.
// 
// THIS SDK IS PROVIDED BY STEINBERG MEDIA TECHNOLOGIES GMBH "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL STEINBERG MEDIA TECHNOLOGIES GMBH BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __vstguieditor__
#define __vstguieditor__

#include "vsteditcontroller.h"
#include "vstgui/vstgui.h"

#if VSTGUI_VERSION_MAJOR < 4
#include "vstgui/cvstguitimer.h"
#define VSTGUI_INT32	long
#else
#define VSTGUI_INT32	int32_t
#endif

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
/** Base class for an edit view using VSTGUI.
\ingroup vstClasses  */
//------------------------------------------------------------------------
class VSTGUIEditor : public EditorView, public VSTGUIEditorInterface, public CBaseObject
{
public:
	/** Constructor. */
	VSTGUIEditor (void* controller, ViewRect* size = 0);
	
	/** Destructor. */
	~VSTGUIEditor ();

	//---Internal function-----
	/** Called when the editor will be opened. */
#if VSTGUI_VERSION_MAJOR >= 4 && VSTGUI_VERSION_MINOR >= 1
	virtual bool PLUGIN_API open (void* parent, const PlatformType& platformType = kDefaultNative) = 0;
#else
	virtual bool PLUGIN_API open (void* parent) = 0;
#endif
	/** Called when the editor will be closed. */
	virtual void PLUGIN_API close () = 0;

	/** Sets the idle rate controlling the parameter update rate. */
	void setIdleRate (int32 millisec);

	//---from CBaseObject---------------
	CMessageResult notify (CBaseObject* sender, const char* message);
	void forget () { EditorView::release (); }
	void remember () { EditorView::addRef (); }
	VSTGUI_INT32 getNbReference () const { return refCount; }

	//---from IPlugView-------
	tresult PLUGIN_API isPlatformTypeSupported (FIDString type);
	tresult PLUGIN_API onSize (ViewRect* newSize);

	//---from VSTGUIEditorInterface-------
	/** Called from VSTGUI when a user begins editing. 
		The default implementation calls performEdit of the EditController. */
	void beginEdit (VSTGUI_INT32 index);
	/** Called from VSTGUI when a user ends editing. 
		The default implementation calls endEdit of the EditController. */
	void endEdit (VSTGUI_INT32 index);

	VSTGUI_INT32 getKnobMode () const;
private:
	//---from IPlugView-------
	tresult PLUGIN_API attached (void* parent, FIDString type);
	tresult PLUGIN_API removed ();
	tresult PLUGIN_API onKeyDown (char16 key, int16 keyMsg, int16 modifiers);
	tresult PLUGIN_API onKeyUp (char16 key, int16 keyMsg, int16 modifiers);
	tresult PLUGIN_API onWheel (float distance);

	CVSTGUITimer* timer;
};

} // namespace Vst
} // namespace Steinberg

#endif	// __vstguieditor__
