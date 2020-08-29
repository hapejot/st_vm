-- | counter |
-- counter <- 1
-- [counter < 10] 
--          whileTrue: [ counter print.
--                       counter <- counter + 1 ]
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

    b0 <- continue l0 tmp 
    b1 <- continue l1 tmp

    message b0 CONT
    param b1
    send whileTrue:
    
b0  block 
    param counter
    c1 <- continue l0end tmp
    param c1
    param max
    send <
l0end :
    return tmp
    goto CONT

l1  block
    param counter
    param c2
    send print

l2  :
    param counter
    param xxxxx
    param incr
    send print

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

    message self c1
    send  value
l1  :
    message tmp Cont
    param c2
    send ifTrue: 
l2  :
    message aBlock c3
    send value
l3  :
    param s self
    param 0 aBlock
    param c blockCont
    end

method value in Block
    tmpvar   self
    tmpvar   cont

    goto self cont
    end

method ifTrue: for True
    tmpvar  self
    tmpvar  CONT
    tmpvar  trueBranch

    goto trueBranch
    end

method ifTrue: for False
    tmpvar  self
    tmpvar  cont
    tmpvar  trueBranch

    goto cont
    end

method print of Symbol
    tmpvar  self
    tmpvar  CONT
	tmpvar	str

    message self CONT
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
    param result
    primitive obj_identical
    end 
