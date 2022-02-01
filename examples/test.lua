function test(n)
    if n <= 0 then
        error("oh no!")
    end

    return test(n-1)
end

test(5)
