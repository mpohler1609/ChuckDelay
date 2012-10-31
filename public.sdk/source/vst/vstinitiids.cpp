//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.5.2
//
// Category    : Helpers
// Filename    : public.sdk/source/vst/vstinitiids.cpp
// Created by  : Steinberg, 10/2009
// Description : Interface symbols file
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

#include "pluginterfaces/base/funknown.h"

#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstmessage.h"
#include "pluginterfaces/vst/ivstunits.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivsthostapplication.h"
#include "pluginterfaces/vst/ivstplugview.h"
#include "pluginterfaces/vst/ivstcontextmenu.h"
#include "pluginterfaces/vst/ivstrepresentation.h"

namespace Steinberg {
namespace Vst {

	//----VST 3.0--------------------------------
	DEF_CLASS_IID (IComponent)
	DEF_CLASS_IID (IAudioProcessor)
	DEF_CLASS_IID (IUnitData)
	DEF_CLASS_IID (IProgramListData)

	DEF_CLASS_IID (IEditController)
	DEF_CLASS_IID (IUnitInfo)

	DEF_CLASS_IID (IConnectionPoint)

	DEF_CLASS_IID (IComponentHandler)
	DEF_CLASS_IID (IUnitHandler)

	DEF_CLASS_IID (IParamValueQueue)
	DEF_CLASS_IID (IParameterChanges)

	DEF_CLASS_IID (IEventList)
	DEF_CLASS_IID (IMessage)

	DEF_CLASS_IID (IHostApplication)
	DEF_CLASS_IID (IAttributeList)

	//----VST 3.0.1--------------------------------
	DEF_CLASS_IID (IMidiMapping)

	//----VST 3.0.2--------------------------------
	DEF_CLASS_IID (IParameterFinder)

	//----VST 3.1----------------------------------
	DEF_CLASS_IID (IComponentHandler2)
	DEF_CLASS_IID (IEditController2)
	DEF_CLASS_IID (IAudioPresentationLatency)

	//---VST 3.1 for AU and VST 2 Wrapper-----------
	DEF_CLASS_IID (IVst3ToVst2Wrapper)
	DEF_CLASS_IID (IVst3ToAUWrapper)

	//----VST 3.5----------------------------------
	DEF_CLASS_IID (INoteExpressionController)
	DEF_CLASS_IID (IKeyswitchController)
	DEF_CLASS_IID (IContextMenuTarget)
	DEF_CLASS_IID (IContextMenu)
	DEF_CLASS_IID (IComponentHandler3)
	DEF_CLASS_IID (IEditControllerHostEditing)
	DEF_CLASS_IID (IXmlRepresentationController)
}
}
