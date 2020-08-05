method main in System
	tmpvar	foo1
	tmpvar	foo2
	global	Foo
	tmpvar	c1	
	tmpvar	c2

	param	#1
	param	#2
	c1 <- continue l1
	param 	c1
	param	Foo
	foo1 <- send	new_a:b:
l1:

	param	11
	param	22
	c2 <- continue l2
	param 	c1
	param 	Foo
	foo2 <-	send	new_a:b:
	end




ivar a in Foo
ivar b in Foo
method new_a:b: in Foo class 
	super
	send	new
	pval	0
	slide	1
	send	set_a:
	pval	1
	slide 	1
	send	set_b:
	end
method set_a: in Foo
	pval 	0
	idef	a
	end
method set_b: in Foo
	pval	0
	idef	b
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


ivar start for Interval
ivar stop for Interval
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
    pvar    s self
    pvar    c cont

    jmp self
    end


method setFrom:to: in Interval
	pval	0
	idef	start
	pval	1
	idef	stop
	end

method ifTrue: for True
    pvar    s self
    pvar    0 block
    pvar    c cont

    jmp block

method ifTrue: for False
    pvar    s self
    pvar    0 block
    pvar    c cont

    jmp cont


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
    pvar    s   self
    pvar    0   aBlock
    pvar    c   cont
    param s self 
    param c l1
    send    r value
l1:
    param s r0
    param 0 l2
    param c cont
    send r ifTrue: 
l2:
    param s aBlock
    param c l3
    send t0 value
l3:
    param s self
    param 0 aBlock
    param c blockCont

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

l1:	
	param   s	stop
	param   0   aValue
    param   c   
	send	<=
	
l2:	
	lval	aValue
	pval	0
	send	value:

l3:	
	ival	step
	lval	aValue
	send	+
	ldef	aValue

	end
