CC = gcc
C++ = g++
LINK = g++

CCFLAGS = $(COMPILER_FLAGS) -c -g
C++FLAGS = $(COMPILER_FLAGS) -c -g -std=c++11
LDFLAGS = $(COMPILER_FLAGS) -g -lm -Lusr/local/lib
LDLIBS = $(COMPILER_FLAGS) -lcurl

INCLUDES = -Iusr/local/include -I./libs -I./libs/curlpp/include -I./libs/json/src -I./libs/googlemap/ -I./libs/timer/ -I./libs/bcm2835/

clean:
	rm -f ./out/*.o ./out/*.a ./out/*.exe

compile_bcm2835:
	$(CC) $(CCFLAGS) ./libs/bcm2835/bcm2835.c -o ./out/bcm2835.o

compile_timer:
	$(C++) $(C++FLAGS) ./libs/timer/timer.cpp -o ./out/timer.o

compile_curlpp:
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/internal/CurlHandle.cpp -o ./out/CurlHandle.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/internal/OptionList.cpp -o ./out/OptionList.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/internal/OptionSetter.cpp -o ./out/OptionSetter.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/internal/SList.cpp -o ./out/SList.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/cURLpp.cpp -o ./out/cURLpp.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Easy.cpp -o ./out/Easy.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Exception.cpp -o ./out/Exception.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Form.cpp -o ./out/Form.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Info.cpp -o ./out/Info.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Multi.cpp -o ./out/Multi.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/OptionBase.cpp -o ./out/OptionBase.o -Iusr/local/include -I./libs/curlpp/include
	$(C++) $(C++FLAGS) -Lusr/local/lib -lcurl ./libs/curlpp/src/curlpp/Options.cpp -o ./out/Options.o -Iusr/local/include -I./libs/curlpp/include

compile_dev_ultrasonic:
	$(C++) $(C++FLAGS) dev_ultrasonic.cpp -o ./out/dev_ultrasonic.o

compile_dev_pca9685:
	$(C++) $(C++FLAGS) dev_pca9685.cpp -o ./out/dev_pca9685.o

compile_dev_servo:
	$(C++) $(C++FLAGS) dev_servo.cpp -o ./out/dev_servo.o

compile_dev_buzzer:
	$(C++) $(C++FLAGS) dev_buzzer.cpp -o ./out/dev_buzzer.o

compile_dev_motor:
	$(C++) $(C++FLAGS) dev_motor.cpp -o ./out/dev_motor.o

compile_app_map:
	$(C++) $(C++FLAGS) app_map.cpp -o ./out/app_map.o $(INCLUDES)

compile_app_autoObstacleAvoidance:
	$(C++) $(C++FLAGS) app_autoObstacleAvoidance.cpp -o ./out/app_autoObstacleAvoidance.o $(INCLUDES)

compile_main_autoObstacleAvoidance:
	$(C++) $(C++FLAGS) app_main_autoObstacleAvoidance.cpp -o ./out/app_main_autoObstacleAvoidance.o $(INCLUDES)

compile_app_autoRun_map:
	$(C++) $(C++FLAGS) app_autoRun_map.cpp -o ./out/app_autoRun_map.o $(INCLUDES)

compile_app_main_followingMap:
	$(C++) $(C++FLAGS) app_main_followingMap.cpp -o ./out/app_main_followingMap.o $(INCLUDES)

compile_test:
	$(C++) $(C++FLAGS) test.cpp -o ./out/test.o $(INCLUDES)

compile_test_main:
	$(C++) $(C++FLAGS) test_main.cpp -o ./out/test_main.o $(INCLUDES)
	
app_autoRun_obsAvoid:
	@echo Build Start!
	make clean
	make compile_bcm2835
	make compile_timer
	make compile_curlpp
	make compile_dev_ultrasonic
	make compile_dev_pca9685
	make compile_dev_servo
	make compile_dev_buzzer
	make compile_dev_motor
	make compile_app_map
	make compile_app_autoObstacleAvoidance
	make compile_main_autoObstacleAvoidance

	$(LINK) -o ./out/app_autoRun					\
					./out/bcm2835.o					\
					./out/timer.o					\
					./out/CurlHandle.o				\
					./out/OptionList.o				\
					./out/OptionSetter.o			\
					./out/SList.o					\
					./out/cURLpp.o					\
					./out/Exception.o				\
					./out/OptionBase.o				\
					./out/Options.o					\
					./out/Multi.o 					\
					./out/Info.o					\
					./out/Form.o					\
					./out/Easy.o					\
					./out/dev_ultrasonic.o			\
					./out/dev_pca9685.o				\
					./out/dev_servo.o				\
					./out/dev_buzzer.o				\
					./out/dev_motor.o				\
					./out/app_map.o					\
					./out/app_autoObstacleAvoidance.o					\
					./out/app_main_autoObstacleAvoidance.o				\
					$(LDFLAGS) $(LDLIBS)
	@echo Build Complete with no error!

app_autoMapRun:
	@echo Build Start!
	make clean
	make compile_bcm2835
	make compile_timer
	make compile_curlpp
	make compile_dev_ultrasonic
	make compile_dev_pca9685
	make compile_dev_servo
	make compile_dev_buzzer
	make compile_dev_motor
	make compile_app_map
	make compile_app_autoRun_map
	make compile_app_main_followingMap

	$(LINK) -o ./out/app_autoRun					\
					./out/bcm2835.o					\
					./out/timer.o					\
					./out/CurlHandle.o				\
					./out/OptionList.o				\
					./out/OptionSetter.o			\
					./out/SList.o					\
					./out/cURLpp.o					\
					./out/Exception.o				\
					./out/OptionBase.o				\
					./out/Options.o					\
					./out/Multi.o 					\
					./out/Info.o					\
					./out/Form.o					\
					./out/Easy.o					\
					./out/dev_ultrasonic.o			\
					./out/dev_pca9685.o				\
					./out/dev_servo.o				\
					./out/dev_buzzer.o				\
					./out/dev_motor.o				\
					./out/app_map.o					\
					./out/app_autoRun_map.o				\
					./out/app_main_followingMap.o	\
					$(LDFLAGS) $(LDLIBS)
	@echo Build Complete with no error!

test_all:
	@echo Build Start!
	make clean
	make compile_bcm2835
	make compile_timer
	make compile_curlpp
	make compile_dev_ultrasonic
	make compile_dev_pca9685
	make compile_dev_servo
	make compile_dev_buzzer
	make compile_dev_motor
	make compile_app_map
	make compile_app_autoRun
	make compile_app_main
	make compile_test
	make compile_test_main

	$(LINK) -o ./out/app_autoRun					\
					./out/bcm2835.o					\
					./out/timer.o					\
					./out/CurlHandle.o				\
					./out/OptionList.o				\
					./out/OptionSetter.o			\
					./out/SList.o					\
					./out/cURLpp.o					\
					./out/Exception.o				\
					./out/OptionBase.o				\
					./out/Options.o					\
					./out/Multi.o 					\
					./out/Info.o					\
					./out/Form.o					\
					./out/Easy.o					\
					./out/dev_ultrasonic.o			\
					./out/dev_pca9685.o				\
					./out/dev_servo.o				\
					./out/dev_buzzer.o				\
					./out/dev_motor.o				\
					./out/app_map.o					\
					./out/app_autoRun.o				\
					./out/test.o					\
					./out/test_main.o				\
					$(LDFLAGS) $(LDLIBS)
	@echo Build Complete with no error!

