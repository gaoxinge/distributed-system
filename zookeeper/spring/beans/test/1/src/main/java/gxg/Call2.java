package gxg;

import gxg.beans.Comp;
import gxg.beans.Comp1;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Call2 {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext(Comp.class, Comp1.class);
//        ctx.start();
        System.out.println(ctx.getBean("Comp"));
        System.out.println(ctx.getBean("testBean"));
    }
}
