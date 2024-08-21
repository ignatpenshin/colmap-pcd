docker build -t="colmap-pcd_dev:latest" .
docker run -e QT_XCB_GL_INTEGRATION=xcb_egl -e DISPLAY=:0 -v /tmp/.X11-unix:/tmp/.X11-unix --gpus all --privileged -w /working -v $1:/working -it colmap:latest colmap gui
