package com.ilyakrn.gateway.config;

import com.ilyakrn.gateway.routes.IdentityServiceRoutes;
import com.ilyakrn.gateway.routes.PlaneServiceRoutes;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.gateway.route.RouteLocator;
import org.springframework.cloud.gateway.route.builder.RouteLocatorBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Slf4j
@Configuration
public class RoutesConfig {

    @Autowired
    IdentityServiceRoutes identityServiceRoutes;
    @Autowired
    PlaneServiceRoutes planeServiceRoutes;
    @Autowired
    PropertiesConfig cfg;


    @Bean
    public RouteLocator routes(RouteLocatorBuilder builder) {
        RouteLocatorBuilder.Builder b = builder.routes();

        String[] mappingsIdentity = identityServiceRoutes.getMappings();
        for (String mapping : mappingsIdentity) {
            b = b.route(p -> p
                    .path(mapping)
                    .filters(f -> f.addRequestHeader(cfg.getServiceTokenHeader(), cfg.getServiceToken()))
                    .uri(identityServiceRoutes.getUrl()));
            log.info("added route: {} {}", identityServiceRoutes.getUrl(), mapping);
        }

        String[] mappingsPlane = planeServiceRoutes.getMappings();
        for (String mapping : mappingsPlane) {
            b = b.route(p -> p
                    .path(mapping)
                    .filters(f -> f.addRequestHeader(cfg.getServiceTokenHeader(), cfg.getServiceToken()))
                    .uri(planeServiceRoutes.getUrl()));
            log.info("added route: {} {}", planeServiceRoutes.getUrl(), mapping);
        }
        return b.build();
    }
}
