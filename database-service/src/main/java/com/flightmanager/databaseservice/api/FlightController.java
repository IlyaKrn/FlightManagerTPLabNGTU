package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.FlightModel;
import com.flightmanager.databaseservice.repos.FlightRepo;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Slf4j
@RestController
public class FlightController {

    @Autowired
    private FlightRepo repo;


    @GetMapping("${mapping.flight.get}")
    public ResponseEntity<List<FlightModel>> get(
            @RequestParam(value = "id", required = false) Long id,
            @RequestParam(value = "timestampStart", required = false) Long timestampStart,
            @RequestParam(value = "timestampEnd", required = false) Long timestampEnd,
            @RequestParam(value = "dispatcherId", required = false) Long dispatcherId,
            @RequestParam(value = "planeId", required = false) Long planeId,
            @RequestParam(value = "airportId", required = false) Long airportId
    ) {
        try {
            List<FlightModel> models = repo.findAll();
            if (id != null)
                models = models.stream().filter(m -> m.getId().equals(id)).collect(Collectors.toList());
            if (timestampStart != null)
                models = models.stream().filter(m -> m.getTimestampStart().equals(timestampStart)).collect(Collectors.toList());
            if (timestampEnd != null)
                models = models.stream().filter(m -> m.getTimestampEnd().equals(timestampEnd)).collect(Collectors.toList());
            if (dispatcherId != null)
                models = models.stream().filter(m -> m.getDispatcherId().equals(dispatcherId)).collect(Collectors.toList());
            if (planeId != null)
                models = models.stream().filter(m -> m.getPlaneId().equals(planeId)).collect(Collectors.toList());
            if (airportId != null)
                models = models.stream().filter(m -> m.getAirportId().equals(airportId)).collect(Collectors.toList());
            log.info("get flight successful (" + models.size() + " entities)");
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            log.warn("get flight failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.flight.create}")
    public ResponseEntity<FlightModel> create(@RequestBody FlightModel data) {
        try {
            data.setId(0L);
            if (containsNullFields(data)) {
                log.warn("create flight failed: invalid data");
                return ResponseEntity.status(400).build();
            }
            FlightModel model = repo.save(data);
            log.info("create flight successful: id=" + model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.warn("create flight failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.flight.update}")
    public ResponseEntity<FlightModel> update(@RequestBody FlightModel data, @RequestParam("update") String update) {
        try {
            if (data.getId() == null) {
                log.warn("update flight failed: id not provided");
                return ResponseEntity.status(400).build();
            }
            FlightModel fromDB = repo.findById(data.getId()).orElse(null);
            if (fromDB == null) {
                log.warn("update flight failed: flight not found");
                return ResponseEntity.status(400).build();
            }

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if (!fields.contains("timestampStart"))
                data.setTimestampStart(fromDB.getTimestampStart());
            if (!fields.contains("timestampEnd"))
                data.setTimestampEnd(fromDB.getTimestampEnd());
            if (!fields.contains("dispatcherId"))
                data.setDispatcherId(fromDB.getDispatcherId());
            if (!fields.contains("planeId"))
                data.setPlaneId(fromDB.getPlaneId());
            if (!fields.contains("airportId"))
                data.setAirportId(fromDB.getAirportId());
            if (containsNullFields(data)) {
                log.warn("update flight failed: invalid data");
                return ResponseEntity.status(400).build();
            }

            FlightModel model = repo.save(data);
            log.info("update flight successful: id=" + model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.warn("update flight failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.flight.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try {
            repo.deleteById(id);
            log.info("delete flight successful: id=" + id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            log.warn("delete flight failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(FlightModel data) {
        return data.getTimestampStart() == null ||
                data.getTimestampEnd() == null ||
                data.getDispatcherId() == null ||
                data.getPlaneId() == null ||
                data.getAirportId() == null;
    }

}
