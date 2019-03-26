#ifndef __GALILEO_WRAPPER_H__
#define __GALILEO_WRAPPER_H__

#include <boost/python.hpp>

#ifdef _WIN32
#include "GalileoSDK.h"
#else
#include <GalileoSDK/GalileoSDK.h>
#endif

namespace GalileoWrap {
    
    typedef std::vector<GalileoSDK::ServerInfo> ServersList;

    class with_gil
    {
    public:
        with_gil() { state_ = PyGILState_Ensure(); }
        ~with_gil() { PyGILState_Release(state_); }

        with_gil(const with_gil&) = delete;
        with_gil& operator=(const with_gil&) = delete;
    private:
        PyGILState_STATE state_;
    };

    class py_callable
    {
    public:

        /// @brief Constructor that assumes the caller has the GIL locked.
        py_callable(const boost::python::object& object)
        {
            with_gil gil;
            object_ = *object;
        }

        // Use default copy-constructor and assignment-operator.
        py_callable(const py_callable&) = default;
        py_callable& operator=(const py_callable&) = default;

        template <typename ...Args>
        void operator()(Args... args)
        {
            // Lock the GIL as the python object is going to be invoked.
            with_gil gil;
            (object_)(std::forward<Args>(args)...);
        }

    private:
        boost::python::object object_;
    };

    namespace py = boost::python;

    template< typename T >
    inline
        std::vector< T > to_std_vector(const py::object& iterable)
    {
        return std::vector< T >(py::stl_input_iterator< T >(iterable),
            py::stl_input_iterator< T >());
    }

    class GalileoWrap
    {
    public:
        GalileoWrap();
        GalileoSDK::GALILEO_RETURN_CODE
            Connect(std::string targetID, bool auto_connect, int timeout,
                boost::python::object OnConnect,
                boost::python::object OnDisconnect
            );
        GalileoSDK::GALILEO_RETURN_CODE
            ConnectIOT(std::string targetID, int timeout, std::string password,
                boost::python::object OnConnect,
                boost::python::object OnDisconnect
            );
        ServersList GetServersOnline();
        boost::python::object GetCurrentServer();
        GalileoSDK::GALILEO_RETURN_CODE PublishTest();
        GalileoSDK::GALILEO_RETURN_CODE SendCMD(boost::python::list cmd);
        GalileoSDK::GALILEO_RETURN_CODE StartNav();
        GalileoSDK::GALILEO_RETURN_CODE StopNav();
        GalileoSDK::GALILEO_RETURN_CODE SetGoal(int goalIndex);
        GalileoSDK::GALILEO_RETURN_CODE PauseGoal();
        GalileoSDK::GALILEO_RETURN_CODE ResumeGoal();
        GalileoSDK::GALILEO_RETURN_CODE CancelGoal();
        GalileoSDK::GALILEO_RETURN_CODE InsertGoal(float x, float y);
        GalileoSDK::GALILEO_RETURN_CODE ResetGoal();
        GalileoSDK::GALILEO_RETURN_CODE SetSpeed(float vLinear, float vAngle);
        GalileoSDK::GALILEO_RETURN_CODE Shutdown();
        GalileoSDK::GALILEO_RETURN_CODE SetAngle(int sign, int angle);
        GalileoSDK::GALILEO_RETURN_CODE StartLoop();
        GalileoSDK::GALILEO_RETURN_CODE StopLoop();
        GalileoSDK::GALILEO_RETURN_CODE SetLoopWaitTime(int time);
        GalileoSDK::GALILEO_RETURN_CODE StartMapping();
        GalileoSDK::GALILEO_RETURN_CODE StopMapping();
        GalileoSDK::GALILEO_RETURN_CODE SaveMap();
        GalileoSDK::GALILEO_RETURN_CODE UpdateMap();
        GalileoSDK::GALILEO_RETURN_CODE StartChargeLocal();
        GalileoSDK::GALILEO_RETURN_CODE StopChargeLocal();
        GalileoSDK::GALILEO_RETURN_CODE SaveChargeBasePosition();
        GalileoSDK::GALILEO_RETURN_CODE StartCharge(float x, float y);
        GalileoSDK::GALILEO_RETURN_CODE StopCharge();
        int MoveTo(float x, float y);
        int GetGoalNum();
        boost::python::object GetCurrentStatus();
        void SetCurrentStatusCallback(boost::python::object callback);
        void SetGoalReachedCallback(boost::python::object callback);
        GalileoSDK::GALILEO_RETURN_CODE WaitForGoal(int goalID);
        GalileoSDK::GALILEO_RETURN_CODE SendAudio(std::string audio);
        bool CheckServerOnline(std::string targetID);
        ~GalileoWrap();
    private:
        GalileoSDK::GalileoSDK* sdk;
    };
}

#endif