
#ifndef HAL_CAN_H_
#define HAL_CAN_H_

#include "status.h"
#include "can_common.h"

namespace HAL {

using CanTxCallback = void(*)();
using CanRxCallback = void(*)(CanMessage *message);

template <class HwModule, class BaudrateType>
class Can
{
    public:
        using Baudrate = BaudrateType;

        /* Init */
        static inline void init(CanRxCallback rxCallback, CanTxCallback txCallback)
        {
            HwModule::init(rxCallback, txCallback);
        }

        /* Config the speed and start */
        static inline void begin(CanBaubrate speed)
        {
            HwModule::begin(speed);
        };

        /* Send the data */
        static inline Status send(CanMessage *message)
        {
            Status status = Status::BUSY;

            if(HwModule::send(message) == true)
            {
                status = Status::OK;
            }
            
            return status;
        };

        /* static inline Status addFilter(uint32_t filterValue)
        {
            Status status = Status::OVERFLOW;

            if(HwModule::addFilter(filterValue) == true)
            {
                status = Status::OK;
            }
            
            return status;
        }; */

        /* static inline Status removeFilter(uint32_t filterValue)
        {
            Status status = Status::NOT_FOUND;

            if(HwModule::removeFilter(filterValue) == true)
            {
                status = Status::OK;
            }

            return status;
        } */

        /* static inline void addBroadcastFilter(void)
        {
            HwModule::addBroadcastFilter();
        }

        static inline void removeBroadcastFilter(void)
        {
            HwModule::removeBroadcastFilter();
        }

        static inline void removeAllFilters(void)
        {
            HwModule::removeAllFilters();
        } */
};

}

#endif /* HAL_CAN_H_ */
