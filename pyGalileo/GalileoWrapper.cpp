#define BOOST_PYTHON_STATIC_LIB
#include "GalileoWrapper.h"
namespace GalileoWrap {

    GalileoWrap::GalileoWrap()
    {
        sdk = new GalileoSDK::GalileoSDK();
    }

    GalileoWrap::~GalileoWrap()
    {
        sdk->~GalileoSDK();
        free(sdk);
    }


    GalileoSDK::GALILEO_RETURN_CODE
        GalileoWrap::Connect(std::string targetID, bool auto_connect, int timeout,
            boost::python::object OnConnect, boost::python::object OnDisconnect) {
        return sdk->Connect(targetID, auto_connect, timeout,
            boost::python::extract<void(*)(GalileoSDK::GALILEO_RETURN_CODE, std::string)>(OnConnect),
            boost::python::extract<void(*)(GalileoSDK::GALILEO_RETURN_CODE, std::string)>(OnDisconnect));
    }

    ServersList GalileoWrap::GetServersOnline() {
        return sdk->GetServersOnline();
    }
}
