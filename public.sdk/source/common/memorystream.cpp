//-----------------------------------------------------------------------------
// Project     : SDK Core
// Version     : 1.0
//
// Category    : Common Classes
// Filename    : memorystream.cpp
// Created by  : Steinberg, 03/2008
// Description : IBStream Implementation for memory blocks
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

#include "memorystream.h"
#include "pluginterfaces/base/futils.h"
#include <stdlib.h>

namespace Steinberg {

//-----------------------------------------------------------------------------
IMPLEMENT_FUNKNOWN_METHODS (MemoryStream, IBStream, IBStream::iid)
static const TSize kMemGrowAmount = 4096;

//-----------------------------------------------------------------------------
MemoryStream::MemoryStream (void* data, TSize length)
: memory ((char*)data)
, memorySize (length)
, size (length)
, ownMemory (false)
, allocationError (false)
, cursor (0)
{ 
	FUNKNOWN_CTOR 
}

//-----------------------------------------------------------------------------
MemoryStream::MemoryStream ()
: memory (0)
, memorySize (0)
, size (0)
, ownMemory (true)
, allocationError (false)
, cursor (0)
{
}

//-----------------------------------------------------------------------------
MemoryStream::~MemoryStream () 
{ 
	if (ownMemory)
		if (memory)
			::free (memory);

	FUNKNOWN_DTOR 
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API MemoryStream::read (void* data, int32 numBytes, int32* numBytesRead)
{
	if (memory == 0)
	{
		if (allocationError)
			return kOutOfMemory;
		numBytes = 0;
	}
	else
	{		
		// Does read exceed size ?
		if (cursor + numBytes > size)
		{
			int32 maxBytes = int32 (size - cursor);

			// Has length become zero or negative ?
			if (maxBytes <= 0) 
			{
				cursor = size;
				numBytes = 0;
			}
			else
				numBytes = maxBytes;
		}
		
		if (numBytes)
		{
			memcpy (data, &memory[cursor], numBytes);
			cursor += numBytes;
		}
	}

	if (numBytesRead)
		*numBytesRead = numBytes;

	return kResultTrue;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API MemoryStream::write (void* buffer, int32 numBytes, int32* numBytesWritten)
{
	if (allocationError)
		return kOutOfMemory;
	if (buffer == 0)
		return kInvalidArgument;

	// Does write exceed size ?
	TSize requiredSize = cursor + numBytes;
	if (requiredSize > size) 
	{		
		if (requiredSize > memorySize)
			setSize (requiredSize);
		else
			size = requiredSize;
	}
	
	// Copy data
	if (memory && cursor >= 0 && numBytes > 0)
	{
		memcpy (&memory[cursor], buffer, numBytes);
		// Update cursor
		cursor += numBytes;
	}
	else
		numBytes = 0;

	if (numBytesWritten)
		*numBytesWritten = numBytes;

	return kResultTrue;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API MemoryStream::seek (int64 pos, int32 mode, int64* result)
{
	switch (mode) 
	{
		case kIBSeekSet:
			cursor = pos;
			break;
		case kIBSeekCur:
			cursor = cursor + pos;
			break;
		case kIBSeekEnd:
			cursor = size + pos;
			break;
	}

	if (ownMemory == false)
		if (cursor > memorySize)
			cursor = memorySize;

	if (result)
		*result = cursor;

	return kResultTrue;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API MemoryStream::tell  (int64* pos)
{
	if (!pos)
		return kInvalidArgument;

	*pos = cursor;
	return kResultTrue;
}

//------------------------------------------------------------------------
TSize MemoryStream::getSize ()
{
	return size;
}

//------------------------------------------------------------------------
void MemoryStream::setSize (TSize s)
{
	if (s <= 0)
	{
		if (ownMemory)
			if (memory)
				free (memory);

		memory = 0;
		memorySize = 0;
		size = 0;
		cursor = 0;
		return;
	}

	TSize newMemorySize = (((Max (memorySize, s) - 1) / kMemGrowAmount) + 1) * kMemGrowAmount;
	if (newMemorySize == memorySize)
	{
		size = s;
		return;
	}

	if (memory && ownMemory == false)
	{
		allocationError = true;
		return;	
	}

	ownMemory = true;
	char* newMemory = 0;

	if (memory)
	{
		newMemory = (char*)realloc (memory, (size_t)newMemorySize);
		if (newMemory == 0 && newMemorySize > 0)
		{
			newMemory = (char*)malloc ((size_t)newMemorySize);
			if (newMemory)
			{
				memcpy (newMemory, memory, (size_t)Min (newMemorySize, memorySize));           
				free (memory);
			}		
		}
	}
	else
		newMemory = (char*)malloc ((size_t)newMemorySize);

	if (newMemory == 0)
	{
		if (newMemorySize > 0)
			allocationError = true;

		memory = 0;
		memorySize = 0;
		size = 0;
		cursor = 0;
	}
	else
	{
		memory = newMemory;
		memorySize = newMemorySize;
		size = s;
	}
}

//------------------------------------------------------------------------
char* MemoryStream::getData ()
{
	return memory;
}

//------------------------------------------------------------------------
char* MemoryStream::detachData ()
{
	if (ownMemory)
	{
		char* result = memory;
		memory = 0;
		memorySize = 0;
		size = 0;
		cursor = 0;
		return result;
	}
	return 0;
}

//------------------------------------------------------------------------
bool MemoryStream::truncate ()
{
	if (ownMemory == false)
		return false;

	if (memorySize == size)
		return true;

	memorySize = size;
	
	if (memorySize == 0)
	{
		if (memory)
		{
			free (memory);
			memory = 0;
		}
	}
	else
	{
		if (memory)
		{
			char* newMemory = (char*)realloc (memory, (size_t)memorySize);
			if (newMemory)
				memory = newMemory;
		}
	}
	return true;
}

//------------------------------------------------------------------------
bool MemoryStream::truncateToCursor ()
{
	size = cursor;
	return truncate ();
}

} // namespace
