cat ../dreamvu_pal_navigation/cmake_template/header.txt > ../dreamvu_pal_navigation/CMakeLists.txt
echo "set(PAL_INCLUDE_DIR" `pwd`/../include ")" >> ../dreamvu_pal_navigation/CMakeLists.txt
echo "set(PAL_LIBRARY" `pwd`/../lib/libPAL.so  `pwd`/../lib/libPAL_DE.so ")" >> ../dreamvu_pal_navigation/CMakeLists.txt
cat ../dreamvu_pal_navigation/cmake_template/footer.txt >> ../dreamvu_pal_navigation/CMakeLists.txt
