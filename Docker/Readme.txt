docker search ubuntu
docker run -it ubuntu
docker ps -a
docker exec -it 8052788a0748 "/bin/bash"
docker start 8052788a0748 
docker cp /home/mohammad/Project/MachineTest/Application/Build/App  8052788a0748:/home/Build/
docker exec -it 8052788a0748 /home/Build/App -s /home/Build/ -p 2000
docker export 8052788a0748 /App.tar
docker import C:\Users\lotfi\Desktop\App.tar app
docker run -t -i app /bin/bash

