/*
 * Copyright 1999-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * $Id$
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLNotationDecl.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XMLNotationDecl: Constructors and operators
// ---------------------------------------------------------------------------
XMLNotationDecl::XMLNotationDecl(MemoryManager* const manager) :

    fId(0)
    , fNameSpaceId(0)
    , fName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
}

XMLNotationDecl::XMLNotationDecl( const XMLCh* const   notName
                                , const XMLCh* const   pubId
                                , const XMLCh* const   sysId
                                , const XMLCh* const   baseURI
                                , MemoryManager* const manager) :
    fId(0)
    , fNameSpaceId(0)
    , fName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
    try
    {
        fName = XMLString::replicate(notName, fMemoryManager);
        fPublicId = XMLString::replicate(pubId, fMemoryManager);
        fSystemId = XMLString::replicate(sysId, fMemoryManager);
        fBaseURI  = XMLString::replicate(baseURI, fMemoryManager);
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch(...)
    {
        cleanUp();
    }
}

XMLNotationDecl::~XMLNotationDecl()
{
    cleanUp();
}


// -----------------------------------------------------------------------
//  Setter methods
// -----------------------------------------------------------------------
void XMLNotationDecl::setName(const XMLCh* const notName)
{
    // Clean up the current name stuff and replicate the passed name
    if (fName)
        fMemoryManager->deallocate(fName);

    fName = XMLString::replicate(notName, fMemoryManager);
}



// ---------------------------------------------------------------------------
//  XMLNotationDecl: Private helper methods
// ---------------------------------------------------------------------------
void XMLNotationDecl::cleanUp()
{
    fMemoryManager->deallocate(fName);
    fMemoryManager->deallocate(fPublicId);
    fMemoryManager->deallocate(fSystemId);
    fMemoryManager->deallocate(fBaseURI);
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_TOCREATE(XMLNotationDecl)

void XMLNotationDecl::serialize(XSerializeEngine& serEng)
{
    if (serEng.isStoring())
    {
        serEng<<fId;
        serEng<<fNameSpaceId;
        serEng.writeString(fName);
        serEng.writeString(fPublicId);
        serEng.writeString(fSystemId);
        serEng.writeString(fBaseURI);
    }
    else
    {
        serEng>>fId;
        serEng>>fNameSpaceId;
        serEng.readString(fName);
        serEng.readString(fPublicId);
        serEng.readString(fSystemId);
        serEng.readString(fBaseURI);
    }
}


XERCES_CPP_NAMESPACE_END
