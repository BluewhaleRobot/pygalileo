#encoding=utf-8
import pyGalileo
import time


def test_pub():
    sdk = pyGalileo.SDK()
    while True:
        servers = sdk.GetServersOnline()
        if len(servers) == 0:
            print("No Server Found")
        for server in servers:
            print(server.id)
            sdk.Connect("", True, 10000, None, None)
        sdk.PublishTest()
        time.sleep(1)


def test_get_servers_online():
    sdk = pyGalileo.SDK()
    while True:
        servers = sdk.GetServersOnline()
        if len(servers) == 0:
            print("No Server Found")
        for server in servers:
            print(server.id)
            sdk.Connect("", True, 10000, None, None)
        time.sleep(1)


def test_get_current_server():
    sdk = pyGalileo.SDK()
    while True:
        servers = sdk.GetServersOnline()
        if len(servers) == 0:
            print("No Server Found")
        for server in servers:
            print(server.id)
            sdk.Connect("", True, 10000, None, None)
        print(sdk.GetCurrentServer() == None)
        if sdk.GetCurrentServer() != None:
            print(sdk.GetCurrentServer().id)
        time.sleep(1)


def test_sub():
    sdk = pyGalileo.SDK()
    sdk.Connect("", True, 10000, None, None)
    while True:
        status = sdk.GetCurrentStatus()
        if status is not None:
            print(status.power)
        else:
            print("Get status failed")
        time.sleep(1)


def test_connect_with_callback():
    sdk = pyGalileo.SDK()
    connected = False

    def on_connect(status, id):
        # global connected
        print("OnConnect Callback: result " + str(status))
        print("OnConnect Callback: connected to " + id)
        # connected = True
    sdk.Connect("", True, 10000, on_connect, None)
    while not connected:
        time.sleep(1)


def test_function():
    sdk = pyGalileo.SDK()

    def add(a, b):
        print("add called")
        return a + b
    print(str(sdk.apply2(add, 1.0, 2.0)))


connect_callback_flag = False
connected = False


def test_reconnect():
    global connect_callback_flag, connected
    sdk = pyGalileo.SDK()

    def on_connect(status, id):
        global connect_callback_flag, connected
        print("on_connect Callback: result " + str(status))
        print("on_connect Callback: connected to " + id)
        connect_callback_flag = True
        if status == pyGalileo.GALILEO_RETURN_CODE.OK:
            connected = True

    def on_disconnect(status, id):
        global connected
        print("on_disconnect Callback: result " + str(status))
        print("on_disconnect Callback: connected to " + id)
        connected = False

    while True:
        if not connected:
            sdk.Connect("", True, 10000,
                        on_connect, on_disconnect)
            while not connect_callback_flag:
                print("connect_callback_flag" + str(connect_callback_flag))
                time.sleep(1)
            print("out")
            connect_callback_flag = False
        time.sleep(1)
        print("Waitting")


def test_send_galileo_cmd():
    sdk = pyGalileo.SDK()
    if sdk.Connect(
        "71329A5B0F2D68364BB7B44F3F125531E4C7F5BC3BCE2694DFE39B505FF9C730A614FF2790C1",
            True, 10000, None, None) != pyGalileo.GALILEO_RETURN_CODE.OK:
        print("Connect to server failed")
    while True:
        sdk.SendCMD([0x01, 0x01, 0x01, 0x01, 0x01, 0x01])
        time.sleep(1)


def test_nav():
    sdk = pyGalileo.SDK()
    if sdk.Connect(
        "71329A5B0F2D68364BB7B44F3F125531E4C7F5BC3BCE2694DFE39B505FF9C730A614FF2790C1",
            True, 10000, None, None) != pyGalileo.GALILEO_RETURN_CODE.OK:
        print("Connect to server failed")
    status = sdk.GetCurrentStatus()
    print("status: " + str(status.navStatus))
    print("start nav")
    sdk.StartNav()
    time.sleep(20)
    status = sdk.GetCurrentStatus()
    print("status: " + str(status.navStatus))
    print("stop nav")
    sdk.StopNav()
    time.sleep(20)
    status = sdk.GetCurrentStatus()
    print("status: " + str(status.navStatus))
    while True:
        time.sleep(1)


def test_set_speed():
    sdk = pyGalileo.SDK()
    if sdk.Connect(
        "71329A5B0F2D68364BB7B44F3F125531E4C7F5BC3BCE2694DFE39B505FF9C730A614FF2790C1",
            True, 10000, None, None) != pyGalileo.GALILEO_RETURN_CODE.OK:
        print("Connect to server failed")
    while True:
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        sdk.SetSpeed(0.1, 0)
        time.sleep(5)
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        sdk.SetSpeed(0, 1)
        time.sleep(5)
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        sdk.SetSpeed(-0.1, 0)
        time.sleep(5)
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        sdk.SetSpeed(0, -1)
        time.sleep(5)
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        sdk.SetSpeed(0, 0)
        time.sleep(5)
        status = sdk.GetCurrentStatus()
        print("currentSpeedX: " + str(status.currentSpeedX))
        print("currentSpeedTheta: " + str(status.currentSpeedTheta))
        time.sleep(5)


def test_set_angle():
    pass


def test_goals():
    sdk = pyGalileo.SDK()
    if sdk.Connect(
        "71329A5B0F2D68364BB7B44F3F125531E4C7F5BC3BCE2694DFE39B505FF9C730A614FF2790C1",
            True, 10000, None, None) != pyGalileo.GALILEO_RETURN_CODE.OK:
        print("Connect to server failed")
    while True:
        # 开启导航
        sdk.StartNav()
        status = sdk.GetCurrentStatus()
        # 等待正常追踪
        while status.visualStatus != 1 or status.navStatus != 1:
            print("Wait for navigation initialization")
            status = sdk.GetCurrentStatus
            time.sleep(1)

        # 设置目标点
        sdk.SetGoal(0)
        # 等待 goal status
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 1:
            print("Wait for goal start")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal started")
        # 暂停目标
        time.sleep(2)
        sdk.PauseGoal()
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 2:
            print("Wait for goal pause")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal paused")
        # 继续目标
        time.sleep(2)
        sdk.ResumeGoal()
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 1:
            print("Wait for goal resume")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal resumed")
        # 取消目标
        time.sleep(2)
        sdk.CancelGoal()
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 0 or status.targetNumID != -1:
            print("Wait for goal cancel")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal cancelled")
        # 再次设置目标
        time.sleep(2)
        print("Set goal again")
        sdk.SetGoal(0)
        # 完成目标
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 1:
            print("Wait for goal start")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal started")
        while status.targetStatus != 0 or status.targetNumID != 0:
            print("Wait for goal complete")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        # 移动到特定目标
        # 获取当前坐标
        status = sdk.GetCurrentStatus()
        pos0_x = status.currentPosX
        pos0_y = status.currentPosY
        # 再次设置目标，移动至1号目标点
        time.sleep(2)
        print("Set goal again")
        sdk.SetGoal(1)
        # 完成目标
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 1:
            print("Wait for goal start")
            status = sdk.GetCurrentStatus()
            time.sleep()
        print("Goal started")
        while status.targetStatus != 0 or status.targetNumID != 1:
            print("Wait for goal complete")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        # 再次获取坐标
        status = sdk.GetCurrentStatus()
        pos1_x = status.currentPosX
        pos1_y = status.currentPosY
        # 移动至0号和1号之间
        goalNum = 0
        print("Start move to " + (pos0_x + pos1_x) /
              2 + " " + (pos0_y + pos1_y) / 2)
        sdk.MoveTo((pos0_x + pos1_x) / 2, (pos0_y + pos1_y) / 2, goalNum)
        # 等待移动完成
        status = sdk.GetCurrentStatus()
        while status.targetStatus != 1:
            print("Wait for goal start")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Goal started")
        while status.targetStatus != 0 or status.targetNumID != goalNum:
            print("Wait for goal complete")
            status = sdk.GetCurrentStatus()
            time.sleep(1)
        print("Move to " + (pos0_x + pos1_x) / 2 +
              " " + (pos0_y + pos1_y) / 2 + " complete")
        print("All complete")
        while True:
            time.sleep(1)


def test_status_cb():
    pass


def test_goal_reached_cb():
    pass


if __name__ == "__main__":
    test_goals()
