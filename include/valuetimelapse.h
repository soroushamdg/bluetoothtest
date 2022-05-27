struct memInt
{
    int val = 0, old_val = 0;
    memInt(int i) : val(i) {}
    operator int() { return val; }
    void operator=(int i)
    {
        old_val = val;
        val = i;
    }
    int old() { return old_val; }
    int current() { return val; }
    bool changed() { return (val == old_val); }
};

struct memUint8_t
{
    uint8_t val = 0, old_val = 0;
    memUint8_t(uint8_t i) : val(i) {}
    operator uint8_t() { return val; }
    void operator=(uint8_t i)
    {
        old_val = val;
        val = i;
    }
    uint8_t old() { return old_val; }
    uint8_t current() { return val; }
    bool changed() { return (val == old_val); }
};

struct memUint16_t
{
    uint16_t val = 0, old_val = 0;
    memUint16_t(uint16_t i) : val(i) {}
    operator uint16_t() { return val; }
    void operator=(uint16_t i)
    {
        old_val = val;
        val = i;
    }
    uint16_t old() { return old_val; }
    uint16_t current() { return val; }
    bool changed() { return (val == old_val); }
};

struct memString
{
    String val = "", old_val = "";
    memString(String i) : val(i) {}
    operator String() { return val; }
    void operator=(String i)
    {
        old_val = val;
        val = i;
    }
    String old() { return old_val; }
    String current() { return val; }
    bool changed() { return (val == old_val); }
};

void swap(uint16_t &val)
{
    // CONVERTS 0X1234 TO 0X3412 FOR SERIAL COMMUNICATION.
    val = ((val << 8) & 0xFF00) |
          ((val >> 8) & 0x00FF);
}

void swap(unsigned long &val)
{
    val = ((val << 24) & 0xFF000000) |
          ((val << 8) & 0x00FF0000) |
          ((val >> 8) & 0x0000FF00) |
          ((val >> 24) & 0x000000FF);
}

// struct vDouble
// {
//     double val = 0, old_val = 0;
//     vDouble(double i) : val(i) {}
//     operator double() { return val; }
//     void operator=(double i)
//     {
//         old_val = val;
//         val = i;
//     }
//     double old() { return old_val; }
// };

// struct vFloat
// {
//     float val = 0, old_val = 0;
//     vFloat(float i) : val(i) {}
//     operator float() { return val; }
//     void operator=(float i)
//     {
//         old_val = val;
//         val = i;
//     }
//     float old() { return old_val; }
// };

// struct vChar
// {
//     char val = 0, old_val = 0;
//     vChar(char i) : val(i) {}
//     operator char() { return val; }
//     void operator=(char i)
//     {
//         old_val = val;
//         val = i;
//     }
//     char old() { return old_val; }
// };
