#include <cstdio>

extern "C" {
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}
#include <fcntl.h> 
#include <sys/ioctl.h> 

int main(int argc, char ** argv)
{

    int file;
    int adapter_nr = 1;
    char filename[20];
    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        return(1);
    }

    int addr = 0x40;
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        return(1);
        return(1);
    }

    __u8 reg = 0x05;
    __s32 res;

    res = i2c_smbus_read_word_data(file, reg);

    return 0;

}