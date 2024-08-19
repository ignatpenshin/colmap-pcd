#docker pull colmap/colmap:latest
#docker run --gpus all -e QT_XCB_GL_INTEGRATION=xcb_egl -e DISPLAY=:0 -v /tmp/.X11-unix:/tmp/.X11-unix -w /working -v $1:/working -it colmap/colmap:latest
docker run --gpus all -e QT_XCB_GL_INTEGRATION=xcb_egl -e DISPLAY=:0 -v /tmp/.X11-unix:/tmp/.X11-unix -w /working -v /home/ignat/Apps/colmap-pcd:/working -it colmap-pcd
