// Copyright 2013-present Facebook. All Rights Reserved.

#ifndef __pbxproj_PBX_ContainerItemProxy_h
#define __pbxproj_PBX_ContainerItemProxy_h

#include <pbxproj/PBX/Project.h>
#include <pbxproj/PBX/Target.h>

namespace pbxproj { namespace PBX {

class ContainerItemProxy : public Object {
public:
    typedef std::shared_ptr <ContainerItemProxy> shared_ptr;

private:
    FileReference::shared_ptr _containerPortal;
    uint32_t                  _proxyType;
    std::string               _remoteGlobalIDString;
    std::string               _remoteInfo;

public:
    ContainerItemProxy();

public:
    inline FileReference::shared_ptr const &containerPortal() const
    { return _containerPortal; }

public:
    inline uint32_t proxyType() const
    { return _proxyType; }

public:
    inline std::string const &remoteGlobalIDString() const
    { return _remoteGlobalIDString; }

    inline std::string const &remoteInfo() const
    { return _remoteInfo; }

public:
    bool parse(Context &context, plist::Dictionary const *dict);

public:
    static inline char const *Isa()
    { return ISA::PBXContainerItemProxy; }
};

} }

#endif  // !__pbxproj_PBX_ContainerItemProxy_h
