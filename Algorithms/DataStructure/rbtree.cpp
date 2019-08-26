
/*
left_rotate(T, x)
    y = x.right

    if x.p == T.nil
        T.root = y
    else if x == x.p.left 
        x.p.left = y
    else
        x.p.right = y

    y.p = x.p

    x.right = y.left 
    y.left = x
    x.p = y

    if x.right != T.nil
        x.right.p = x 

*/  

/*
right_rotate(T, y)
    x = y.left 

    if y.p = T.nil 
        T.root = x 
    else if y == y.p.left 
        y.p.left = x 
    else 
        y.p.right = x 
    
    x.p = y.p 

    y.left = x.right
    x.right = y
    y.p = x

    if y.left != T.nil 
        y.left.p = y

*/