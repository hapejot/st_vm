method main in System
    tmpvar  self
    tmpvar  CONT
	tmpvar	foo1
	tmpvar	foo2
	global	Foo
    tmpvar  result

	c1 <- continue l1 result
	c2 <- continue l2 result

	param	Foo
	param 	c1
	param	#1
	param	#2
	foo1 <- send	new_a:b:
l1  :
	param 	Foo
	param 	c2
	param	11
	param	22
	foo2 <-	send	new_a:b:
l2  :
    param result
    param CONT
    result <- send print
	end

-- Requirements:
-- 
-- internal string is treated like an object of class Symbol
-- class symbol has a method <
-- the method < should be expressable in terms of a primitive
-- 'a' < 'b' ifTrue: [ 'correct' print ]
--
method test in System
    tmpvar  self
    tmpvar  CONT
    tmpvar  result
    tmpvar  tmp

	c1 <- continue l1 result
	c2 <- continue l2 tmp

    l_a <- a
    l_b <- b
    message l_a c1
    param l_b
    result <- send <
l2  : 
    l_str <- correct
    param l_str
    param CONT
    tmp <- send print
    finish c2

l1  :
    param result
    param CONT
    param c2
    tmp <- send ifTrue:
    end


-- Requirements:
-- | counter |
-- counter <- 1
-- [counter < 10] 
--          whileTrue: [ counter print.
                        counter <- counter + 1 ]
--
method testLoop in System
    tmpvar  self
    tmpvar  CONT
    tmpvar  result
    tmpvar  tmp
    tmpvar  counter
    tmpvar  max
    tmpvar  incr
    tmpvar  b0

-- save CONT for later
    finish <- CONT
    counter <- #1
    max <- #10
    incr <- #1

    b0 <- block l0  #0
    b1 <- block l1  #0

    param b0
    param CONT
    param b1
    tmp <- send whileTrue:
    
l0  :
    param counter
    c1 <- continue l0end tmp
    param c1
    param max
    result <- send <
l0end :
    goto CONT tmp

l1  :
    param counter
    param c2
    tmp <- send print
l2  : 
    param counter
    param xxxxx
    param incr
    tmp <- send print

    end


method whileTrue: for Block
--  whileTrue: aBlock 
--  	"Evaluate the argument, aBlock, as long as the value  
--  	of the receiver is true. Ordinarily compiled in-line. 
--  	But could also be done in Smalltalk as follows"
--  
--  	^self value
--  		ifTrue: 
--  			[aBlock value.
--  			self whileTrue: aBlock]! !
    tmpvar      self
    tmpvar      Cont
    tmpvar      aBlock
    tmpvar      result
    tmpvar      tmp

    c1 <- continue l1 tmp
    c2 <- continue l2 tmp
    c3 <- continue l3 tmp

    param self 
    param c1
    result <- send  value
l1  :
    param result
    param cont
    param c2
    send r ifTrue: 
l2  :
    param s aBlock
    param c l3
    send t0 value
l3  :
    param s self
    param 0 aBlock
    param c blockCont
    end

instvar a in Foo
instvar b in Foo
method new_a:b: in Foo class 
    tmpvar  self
    tmpvar  CONT
	tmpvar	a
	tmpvar	b
    tmpvar  c1
    tmpvar  t1

    c1 <- continue l1 t1
    param   self
    param c1 
	t1 <- send	new
l1  :
    c2 <- continue l2
    param   t1
    param   c2
    param   a
	t1  <-  send	set_a:
l2  :
    param   t1
    param   CONT
    param   b
	t1  <-  send	set_b:
	end


method new in Foo class
    tmpvar  self
    tmpvar  CONT
    tmpvar t1
    t1 <- new Foo 2
    goto CONT t1
    end

method set_a: in Foo
    tmpvar  self
    tmpvar  CONT
    tmpvar  value
    a <- value
    goto CONT self
	end

method set_b: in Foo
    tmpvar  self
    tmpvar  CONT
    tmpvar  value
    b <- value
    goto CONT self
	end

method print in Foo
    tmpvar  self
    tmpvar  CONT
    tmpvar  result

    c1 <- continue l1 result

    param a
    primitive print
    goto c1 self
l1  :
    param b
    primitive print
    goto CONT result
    end

method to: in SmallInteger
	self
	pval	0
	lookup	Interval
	send	from:to:

	end


-- from: startInteger to: stopInteger 
-- 	"Answer a new instance of me, starting at startInteger, ending and
-- 	stopInteger, and with an interval increment of 1."
-- 
-- 	^self new
-- 		setFrom: startInteger
-- 		to: stopInteger
-- 		by: 1!


instvar start for Interval
instvar stop for Interval
method from:to: in Interval class
	self
	send	new

	pval	0
	slide	1
	pval	1
	slide	1
	send	setFrom:to:

	end

-- setFrom: startInteger to: stopInteger by: stepInteger 
-- 	start _ startInteger.
-- 	stop _ stopInteger.
-- 	step _ stepInteger!

method value in Block
    tmpvar   self
    tmpvar   cont

    call self cont
    end


method setFrom:to: in Interval
	pval	0
	idef	start
	pval	1
	idef	stop
	end

method ifTrue: for True
    tmpvar  self
    tmpvar  CONT
    tmpvar  trueBranch

    goto trueBranch
    end


method ifTrue: for False
    pvar    s self
    pvar    0 block
    pvar    c cont

    jmp cont
    end



method do: in Interval
-- do: aBlock 
-- 	| aValue |
-- 	aValue <- start.
--  [stop <= aValue]
-- 				whileTrue: 
-- 					[aBlock value: aValue.
-- 					aValue _ aValue + step]
    pvar    s   self
    pvar    0   aBlock
    pvar    c   cont
    ivar    start    
	tvar	aValue

	set	    aValue  start
    mkcont  t0  l1 
	mkcont  t1  l2
	param   s   t0
    param   0   t1
    send	whileTrue cont
-- kehrt nie zurück, weil c <- cont

l1  :	
	param   s	stop
	param   0   aValue
    param   c   
	send	<=
	
l2  :	
	lval	aValue
	pval	0
	send	value:

l3  :	
	ival	step
	lval	aValue
	send	+
	ldef	aValue

	end


method print of Symbol
    tmpvar  self
    tmpvar  CONT
	tmpvar	str

    param   self
    param   CONT
    primitive print
    end

method < of Symbol
    tmpvar  self
    tmpvar  CONT
	tmpvar	str
    tmpvar  result

	c1 <- continue l1 result
    message self c1
    param str
    cmp <- primitive sym_compare
l1  :
    message #-1 CONT
    param cmp
    ident <- primitive obj_identical
    end 

method < of SmallInteger
    tmpvar  self
    tmpvar  CONT
	tmpvar	str
    tmpvar  result

	c1 <- continue l1 result
    param self
    param c1
    param str
    primitive int_compare
l1  :
    param #-1
    param CONT
    param result
    primitive obj_identical
    end 
