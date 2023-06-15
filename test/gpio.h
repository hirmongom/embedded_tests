/**
 * RM0401, page 135
 *  6. General-purpose I/Os (GPIO)
 */

#define     __I     volatile const       // Defines 'read only' permissions
#define     __O     volatile             // Defines 'write only' permissions
#define     __IO    volatile             // Defines 'read / write' permissions

typedef struct {
    uint32_t MODER;     // Mode
    uint32_t OTYPER;    // Output type
    uint32_t OSPEEDR;   // Output speed
    uint32_t PUPDR;     // Pull-up/pull-down
    uint32_t IDR;       // Input data
    uint32_t ODR;       // Output data
    uint32_t BSRR;      // Bit set/reset
    uint32_t LCKR;      // Configuration lock
    uint32_t AFRL;      // Alternate function low
    uint32_t AFRH;      // Alternate function high
} GPIO_Type;

#define GPIOA_BASE_ADDR     0x40020000UL
#define GPIOB_BASE_ADDR     0x40020400UL
#define GPIOC_BASE_ADDR     0x40020800UL

#define GPIOA               ((GPIO_Type*)) GPIOA_BASE_ADDR
#define GPIOB               ((GPIO_Type*)) GPIOB_BASE_ADDR
#define GPIOC               ((GPIO_Type*)) GPIOC_BASE_ADDR

void GPIO_Init(void);   // Temporary