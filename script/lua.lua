function hello_world()
    print("hello")
    local status, err = pcall(hello_world)
end
