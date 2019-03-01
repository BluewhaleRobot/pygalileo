#pragma once
#define BOOST_PYTHON_STATIC_LIB
#include <GalileoSDK.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "GalileoWrapper.h"

class World
{
public:
    void set(std::string msg) { mMsg = msg; }
    void many(boost::python::list msgs) {
        long l = len(msgs);
        std::stringstream ss;
        for (long i = 0; i<l; ++i) {
            if (i>0) ss << ", ";
            std::string s = boost::python::extract<std::string>(msgs[i]);
            ss << s;
        }
        mMsg = ss.str();
    }
    std::string greet() { return mMsg; }
    std::string mMsg;
};

BOOST_PYTHON_MODULE(pyGalileo)
{
    using namespace boost::python;
    class_<GalileoWrap::GalileoWrap>("SDK", init<>())
        .def("Connect", &GalileoWrap::GalileoWrap::Connect,
        (boost::python::arg("targetID"), boost::python::arg("auto_connect"), boost::python::arg("timeout"),
            boost::python::arg("OnConnect") = NULL, boost::python::arg("OnDisconnect") = NULL))
        .def("GetServersOnline", &GalileoWrap::GalileoWrap::GetServersOnline)
        ;
    class_<GalileoSDK::ServerInfo>("ServerInfo")
        .def("getMac", &GalileoSDK::ServerInfo::getMac)
        .def("getPassword", &GalileoSDK::ServerInfo::getPassword)
        .def("getIP", &GalileoSDK::ServerInfo::getIP)
        .def("getID", &GalileoSDK::ServerInfo::getID)
        .def("getTimestamp", &GalileoSDK::ServerInfo::getTimestamp)
        .def("getPort", &GalileoSDK::ServerInfo::getPort)
        .def("toJsonString", &GalileoSDK::ServerInfo::toJsonString)
        .def("setMac", &GalileoSDK::ServerInfo::setMac)
        .def("setPassword", &GalileoSDK::ServerInfo::setPassword)
        .def("setIP", &GalileoSDK::ServerInfo::setIP)
        .def("setID", &GalileoSDK::ServerInfo::setID)
        .def("setTimestamp", &GalileoSDK::ServerInfo::setTimestamp)
        .def("setPort", &GalileoSDK::ServerInfo::setPort)
        ;
    class_<GalileoWrap::ServersList>("ServersList")
        .def(vector_indexing_suite<GalileoWrap::ServersList>())
        ;
    enum_<GalileoSDK::GALILEO_RETURN_CODE>("GALILEO_RETURN_CODE")
        .value("OK", GalileoSDK::OK)
        .value("NOT_CONNECTED", GalileoSDK::NOT_CONNECTED)
        .value("INVALIDE_STATE", GalileoSDK::INVALIDE_STATE)
        .value("NO_SERVER_FOUND", GalileoSDK::NO_SERVER_FOUND)
        .value("MULTI_SERVER_FOUND", GalileoSDK::MULTI_SERVER_FOUND)
        .value("NETWORK_ERROR", GalileoSDK::NETWORK_ERROR)
        .value("ALREADY_CONNECTED", GalileoSDK::ALREADY_CONNECTED)
        .value("TIMEOUT", GalileoSDK::TIMEOUT)
        .value("SERVER_ERROR", GalileoSDK::SERVER_ERROR)
        .value("GOAL_CANCELLED", GalileoSDK::GOAL_CANCELLED)
        .value("INVALIDE_GOAL", GalileoSDK::INVALIDE_GOAL)
        ;


}