git submodule init
git submodule update
cd lib/oxygine-framework/
cmake .
make -j3
cd ../oxygine-sound/
git apply ../../sound_CMakeLists.txt.patch
cmake .
make -j3
cd ../../
make -j3
./platphormer
