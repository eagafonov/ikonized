BUILD_DIR := build

.PHONY: all build clean deps configure deb

all: build

deps:
	sudo apt-get install -y \
		qt6-base-dev \
		qt6-base-private-dev \
		qt6-svg-dev \
		libkf6windowsystem-dev \
		libkf6globalaccel-dev \
		libkf6i18n-dev \
		libkf6widgetsaddons-dev \
		libkf6xmlgui-dev \
		libkf6config-dev \
		libkf6configwidgets-dev \
		extra-cmake-modules \
		libxcb-ewmh-dev \
		libxcb-icccm4-dev \
		cmake \
		g++ \
		debhelper \
		fakeroot

configure: $(BUILD_DIR)/Makefile

$(BUILD_DIR)/Makefile: CMakeLists.txt src/CMakeLists.txt
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

build: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR) -j$$(nproc)

clean:
	rm -rf $(BUILD_DIR)

install: build
	cmake --install $(BUILD_DIR)

deb:
	dpkg-buildpackage --root-command=fakeroot --build=binary --unsigned-buildinfo --unsigned-changes
