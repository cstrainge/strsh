
Structured Shell (strsh)

Types

    enum     # With values
    struct   # Multi param
    string   # '' "" ``
    int      # 1024
    float    # 10.24
    bool     # true false
    cmd_ret  # 0 - 255, 0 == true, !0 == false

    collection
    list

    function # User code with params and ret value.
    command  # External command.

    any      # Can be any of the prior.

Examples

    fn adder(a: int, b: int): int
    {
        ret $a + $b
    }

    fn test
    {
        a = 10 ; b = 24

        echo "Testing a function."
        c = adder $a $b

        echo "a: $a + b: $b = $c"
    }

    test
