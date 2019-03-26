#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#ifdef _WIN32
#include "GalileoSDK.h"
#else
#include <GalileoSDK/GalileoSDK.h>
#endif
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

BOOST_PYTHON_MODULE(pygalileo)
{
    using namespace boost::python;
    PyEval_InitThreads();
    class_<GalileoWrap::GalileoWrap>("SDK", init<>())
        .def("Connect", &GalileoWrap::GalileoWrap::Connect,
        (boost::python::arg("targetID"), boost::python::arg("auto_connect"), boost::python::arg("timeout"),
            boost::python::arg("OnConnect") = NULL, boost::python::arg("OnDisconnect") = NULL))
        .def("ConnectIOT", &GalileoWrap::GalileoWrap::ConnectIOT,
        (boost::python::arg("targetID"), boost::python::arg("timeout"), boost::python::arg("password"),
            boost::python::arg("OnConnect") = NULL, boost::python::arg("OnDisconnect") = NULL))
        .def("GetServersOnline", &GalileoWrap::GalileoWrap::GetServersOnline)
        .def("GetCurrentServer", &GalileoWrap::GalileoWrap::GetCurrentServer)
        .def("PublishTest", &GalileoWrap::GalileoWrap::PublishTest)
        .def("SendCMD", &GalileoWrap::GalileoWrap::SendCMD)
        .def("StartNav", &GalileoWrap::GalileoWrap::StartNav)
        .def("StopNav", &GalileoWrap::GalileoWrap::StopNav)
        .def("SetGoal", &GalileoWrap::GalileoWrap::SetGoal)
        .def("StopNav", &GalileoWrap::GalileoWrap::StopNav)
        .def("PauseGoal", &GalileoWrap::GalileoWrap::PauseGoal)
        .def("ResumeGoal", &GalileoWrap::GalileoWrap::ResumeGoal)
        .def("CancelGoal", &GalileoWrap::GalileoWrap::CancelGoal)
        .def("InsertGoal", &GalileoWrap::GalileoWrap::InsertGoal)
        .def("ResetGoal", &GalileoWrap::GalileoWrap::ResetGoal)
        .def("SetSpeed", &GalileoWrap::GalileoWrap::SetSpeed)
        .def("Shutdown", &GalileoWrap::GalileoWrap::Shutdown)
        .def("SetAngle", &GalileoWrap::GalileoWrap::SetAngle)
        .def("StartLoop", &GalileoWrap::GalileoWrap::StartLoop)
        .def("StopLoop", &GalileoWrap::GalileoWrap::StopLoop)
        .def("SetLoopWaitTime", &GalileoWrap::GalileoWrap::SetLoopWaitTime)
        .def("StartMapping", &GalileoWrap::GalileoWrap::StartMapping)
        .def("StopMapping", &GalileoWrap::GalileoWrap::StopMapping)
        .def("SaveMap", &GalileoWrap::GalileoWrap::SaveMap)
        .def("UpdateMap", &GalileoWrap::GalileoWrap::UpdateMap)
        .def("StartChargeLocal", &GalileoWrap::GalileoWrap::StartChargeLocal)
        .def("StopChargeLocal", &GalileoWrap::GalileoWrap::StopChargeLocal)
        .def("SaveChargeBasePosition", &GalileoWrap::GalileoWrap::SaveChargeBasePosition)
        .def("StartCharge", &GalileoWrap::GalileoWrap::StartCharge)
        .def("StopCharge", &GalileoWrap::GalileoWrap::StopCharge)
        .def("MoveTo", &GalileoWrap::GalileoWrap::MoveTo)
        .def("GetGoalNum", &GalileoWrap::GalileoWrap::GetGoalNum)
        .def("GetCurrentStatus", &GalileoWrap::GalileoWrap::GetCurrentStatus)
        .def("SetCurrentStatusCallback", &GalileoWrap::GalileoWrap::SetCurrentStatusCallback)
        .def("SetGoalReachedCallback", &GalileoWrap::GalileoWrap::SetGoalReachedCallback)
        .def("WaitForGoal", &GalileoWrap::GalileoWrap::WaitForGoal)
        .def("SendAudio", &GalileoWrap::GalileoWrap::SendAudio)
        .def("CheckServerOnline", &GalileoWrap::GalileoWrap::CheckServerOnline)
        ;
    class_<GalileoSDK::ServerInfo>("ServerInfo")
        .add_property("mac", &GalileoSDK::ServerInfo::getMac, &GalileoSDK::ServerInfo::setMac)
        .add_property("password", &GalileoSDK::ServerInfo::getPassword, &GalileoSDK::ServerInfo::setPassword)
        .add_property("ip", &GalileoSDK::ServerInfo::getIP, &GalileoSDK::ServerInfo::setIP)
        .add_property("id", &GalileoSDK::ServerInfo::getID, &GalileoSDK::ServerInfo::setID)
        .add_property("timestamp", &GalileoSDK::ServerInfo::getTimestamp, &GalileoSDK::ServerInfo::setTimestamp)
        .add_property("port", &GalileoSDK::ServerInfo::getPort, &GalileoSDK::ServerInfo::setPort)
        .add_property("mac", &GalileoSDK::ServerInfo::getMac, &GalileoSDK::ServerInfo::setMac)
        .add_property("mac", &GalileoSDK::ServerInfo::getMac, &GalileoSDK::ServerInfo::setMac)
        .add_property("mac", &GalileoSDK::ServerInfo::getMac, &GalileoSDK::ServerInfo::setMac)
        .def("toJsonString", &GalileoSDK::ServerInfo::toJsonString)
        ;
    class_<GalileoWrap::ServersList>("ServersList")
        .def(vector_indexing_suite<GalileoWrap::ServersList>())
        ;
    class_<galileo_serial_server::GalileoStatus>("GalileoStatus")
        .def_readwrite("header", &galileo_serial_server::GalileoStatus::header)
        .def_readwrite("navStatus", &galileo_serial_server::GalileoStatus::navStatus)
        .def_readwrite("visualStatus", &galileo_serial_server::GalileoStatus::visualStatus)
        .def_readwrite("mapStatus", &galileo_serial_server::GalileoStatus::mapStatus)
        .def_readwrite("gcStatus", &galileo_serial_server::GalileoStatus::gcStatus)
        .def_readwrite("gbaStatus", &galileo_serial_server::GalileoStatus::gbaStatus)
        .def_readwrite("chargeStatus", &galileo_serial_server::GalileoStatus::chargeStatus)
        .def_readwrite("loopStatus", &galileo_serial_server::GalileoStatus::loopStatus)
        .def_readwrite("power", &galileo_serial_server::GalileoStatus::power)
        .def_readwrite("targetNumID", &galileo_serial_server::GalileoStatus::targetNumID)
        .def_readwrite("targetStatus", &galileo_serial_server::GalileoStatus::targetStatus)
        .def_readwrite("targetDistance", &galileo_serial_server::GalileoStatus::targetDistance)
        .def_readwrite("angleGoalStatus", &galileo_serial_server::GalileoStatus::angleGoalStatus)
        .def_readwrite("controlSpeedX", &galileo_serial_server::GalileoStatus::controlSpeedX)
        .def_readwrite("controlSpeedTheta", &galileo_serial_server::GalileoStatus::controlSpeedTheta)
        .def_readwrite("currentSpeedX", &galileo_serial_server::GalileoStatus::currentSpeedX)
        .def_readwrite("currentSpeedTheta", &galileo_serial_server::GalileoStatus::currentSpeedTheta)
        .def_readwrite("currentPosX", &galileo_serial_server::GalileoStatus::currentPosX)
        .def_readwrite("currentPosY", &galileo_serial_server::GalileoStatus::currentPosY)
        .def_readwrite("currentAngle", &galileo_serial_server::GalileoStatus::currentAngle)
        .def_readwrite("busyStatus", &galileo_serial_server::GalileoStatus::busyStatus)
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