#pragma once
#include <GalileoSDK.h>
#include <boost/python.hpp>

namespace GalileoWrap {
    
    typedef std::vector<GalileoSDK::ServerInfo> ServersList;

    class GalileoWrap
    {
    public:
        GalileoWrap();
        GalileoSDK::GALILEO_RETURN_CODE
            Connect(std::string targetID, bool auto_connect, int timeout,
                boost::python::object OnConnect,
                boost::python::object OnDisconnect
            );
        ServersList GetServersOnline();
        ~GalileoWrap();
    private:
        GalileoSDK::GalileoSDK* sdk;
    };

    static void(*OnConnectCB)(GalileoSDK::GALILEO_RETURN_CODE, std::string);
    static void(*OnDisconnectCB)(GalileoSDK::GALILEO_RETURN_CODE, std::string);
}


