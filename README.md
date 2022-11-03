# Gypard
App for joycons from ali to work on pc.
This project was intended to be commercial, but the development stopped before getting to any configurable state.
It is now works on default settings, without any customiation realized. Have to click RUN button to start the application.
Interface:

![image](https://user-images.githubusercontent.com/89610640/199732781-90847256-5aba-4cb0-86d3-21e423e53388.png)
Tray icon:

![image](https://user-images.githubusercontent.com/89610640/199733199-cf200260-8486-4279-a7b3-1f55af4abe71.png)

Reason why it was frozen: JSL has a bug, which starts loading CPU dramatically, when one of the Joycons is getting disconnected, while the app is running(terminating threads did not help). The creator of the library told me, that he cannot recall the inner structure of this lib, but thinks, that it might be the issue. So he recommended to use another library, but i was not interested in this project anymore. Got some knowledge and experience.
