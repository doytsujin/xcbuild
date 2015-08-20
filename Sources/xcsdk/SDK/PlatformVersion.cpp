// Copyright 2013-present Facebook. All Rights Reserved.

#include <xcsdk/SDK/PlatformVersion.h>

using xcsdk::SDK::PlatformVersion;
using libutil::FSUtil;

PlatformVersion::PlatformVersion()
{
}

bool PlatformVersion::
parse(plist::Dictionary const *dict)
{
    auto PN  = dict->value <plist::String> ("ProjectName");
    auto PBV = dict->value <plist::String> ("ProductBuildVersion");
    auto BV  = dict->value <plist::String> ("BuildVersion");
    auto SV  = dict->value <plist::String> ("SourceVersion");

    if (PN != nullptr) {
        _projectName = PN->value();
    }

    if (PBV != nullptr) {
        _productBuildVersion = PBV->value();
    }

    if (BV != nullptr) {
        _buildVersion = BV->value();
    }

    if (SV != nullptr) {
        _sourceVersion = SV->value();
    }

    return true;
}

PlatformVersion::shared_ptr PlatformVersion::
Open(std::string const &path)
{
    if (path.empty()) {
        errno = EINVAL;
        return nullptr;
    }

    std::string versionFileName = path + "/version.plist";
    if (!FSUtil::TestForRead(versionFileName.c_str()))
        return nullptr;

    std::string realPath = FSUtil::ResolvePath(versionFileName);
    if (realPath.empty())
        return nullptr;

    //
    // Parse property list
    //
    plist::Dictionary *plist = plist::Dictionary::Parse(versionFileName);
    if (plist == nullptr)
        return nullptr;

    //
    // Parse the version dictionary and create the object.
    //
    auto platformVersion = std::make_shared <PlatformVersion> ();

    if (!platformVersion->parse(plist)) {
        platformVersion = nullptr;
    }

    //
    // Release the property list.
    //
    plist->release();

    return platformVersion;
}
