#ifndef HAL_DO_H
#define HAL_DO_H
namespace HAL
{
    template <class HwModule>
    class DO
    {
    public:
        static void init()
        {
            HwModule::init();
            return;
        }

        static void set_signal(uint16_t freq, uint8_t duty)
        {
            HwModule::set_signal(freq, duty);
            return;
        }

        static void enable_pull_up()
        {
            HwModule::enable_pull_up();
            return;
        }

        static void disable_pull_up()
        {
            HwModule::disable_pull_up();
            return;
        }

        static void enable_nv()
        {
            HwModule::enable_nv();
            return;
        }

        static void disable_nv()
        {
            HwModule::disable_nv();
            return;
        }
        
    private:
        
    };
}
#endif