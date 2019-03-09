package gxg;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Call3 {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext("gxg.beans");
//        ctx.start();
        System.out.println(ctx.getBean("Comp"));
        System.out.println(ctx.getBean("testBean"));
    }
}
