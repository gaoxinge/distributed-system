package gxg;

import gxg.beans.Comp;
import gxg.beans.Comp1;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Call1 {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext();
        ctx.register(Comp.class);
        ctx.register(Comp1.class);
        ctx.refresh();
        ctx.start();
        System.out.println(ctx.getBean("Comp"));
        System.out.println(ctx.getBean("testBean"));
    }
}
