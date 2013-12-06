/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package potato.primitives;

import java.math.BigInteger;
import potato.objects.LargeInteger;
import potato.objects.SmallInteger;
import potato.objects.SpecialObjects;
import potato.objects.SqueakObject;

import potato.vm.VM;
import static potato.objects.SpecialObjectConstants.*;

/**
 * This class is responsible for handling Large****tiveInteger primitives.
 * 
 * @author Michael Haupt
 */
public class LargeIntegerPrimitives {
    
    private final PrimitiveHandler fHandler;
    
    public LargeIntegerPrimitives(PrimitiveHandler h) {
        fHandler = h;
    }
    
    //
    // primitives
    //
    
    void primitiveLargeIntegerAdd(Object a, Object b) {
        fHandler.pop2andPushPossiblyCoercedBigIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).add(
                LargeInteger.coerceToBig(b)));
    }
    
    void primitiveLargeIntegerSubtract(Object a, Object b) {
        fHandler.pop2andPushPossiblyCoercedBigIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).subtract(
                LargeInteger.coerceToBig(b)));
    }
    
    void primitiveLargeIntegerMultiply(Object a, Object b) {
        fHandler.pop2andPushPossiblyCoercedBigIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).multiply(
                LargeInteger.coerceToBig(b)));
    }
    
    void primitiveLargeIntegerDivide(Object a, Object b) {
        BigInteger big_b = LargeInteger.coerceToBig(b);
        if(big_b.equals(BigInteger.ZERO))
            throw fHandler.failUnexpected("division by zero");
        BigInteger[] results =
            LargeInteger.getOrCacheBig((SqueakObject)a).divideAndRemainder(big_b);
        // If the remainder is not zero, the result should be a Fraction, which
        // we cannot generate from here, so the primitive must fail.
        if(results[1].equals(BigInteger.ZERO))
            fHandler.pop2andPushPossiblyCoercedBigIfOK(results[0]);
        else
            throw fHandler.failExpected();
    }
    
    void primitiveLargeIntegerIntegralDivide(Object a, Object b) {
        BigInteger big_b = LargeInteger.coerceToBig(b);
        if(big_b.equals(BigInteger.ZERO))
            throw fHandler.failUnexpected("division by zero");
        fHandler.pop2andPushPossiblyCoercedBigIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).divide(big_b));
    }
    
    void primitiveLargeIntegerLT(Object a, Object b) {
        fHandler.pop2andDoBoolIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).compareTo(
                LargeInteger.coerceToBig(b)) < 0);
    }
    
    void primitiveLargeIntegerGT(Object a, Object b) {
        fHandler.pop2andDoBoolIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).compareTo(
                LargeInteger.coerceToBig(b)) > 0);
    }
    
    void primitiveLargeIntegerLE(Object a, Object b) {
        BigInteger big_a = LargeInteger.getOrCacheBig((SqueakObject)a);
        BigInteger big_b = LargeInteger.coerceToBig(b);
        fHandler.pop2andDoBoolIfOK(
            big_a.compareTo(big_b) < 0 || big_a.equals(big_b));
    }
    
    void primitiveLargeIntegerGE(Object a, Object b) {
        BigInteger big_a = LargeInteger.getOrCacheBig((SqueakObject)a);
        BigInteger big_b = LargeInteger.coerceToBig(b);
        fHandler.pop2andDoBoolIfOK(
            big_a.compareTo(big_b) > 0 || big_a.equals(big_b));
    }
    
    void primitiveLargeIntegerModulo(Object a, Object b) {
        BigInteger big_b = LargeInteger.coerceToBig(b);
        if(big_b.equals(BigInteger.ZERO))
            throw fHandler.failUnexpected("division by zero");
        fHandler.pop2andPushPossiblyCoercedBigIfOK(
            LargeInteger.getOrCacheBig((SqueakObject)a).mod(big_b));
    }
    
    void primitiveLargeIntegerQuo(Object a, Object b) {
        BigInteger big_b = LargeInteger.coerceToBig(b);
        if(big_b.equals(BigInteger.ZERO))
            throw fHandler.failUnexpected("division by zero");
        BigInteger[] results =
            LargeInteger.getOrCacheBig((SqueakObject)a).divideAndRemainder(big_b);
        // The idea about quo is to round towards zero. That is, *if* there *is*
        // a remainder, we have to check whether the result is positive (and
        // round it down) or negative (and ignore it because we can't create
        // LargeNegativeIntegers anyway from here right now.
        if(results[1].equals(BigInteger.ZERO) || results[0].signum() > 0)
            fHandler.pop2andPushPossiblyCoercedBigIfOK(results[0]);
        else
            throw fHandler.failExpected();
    }
    
}
