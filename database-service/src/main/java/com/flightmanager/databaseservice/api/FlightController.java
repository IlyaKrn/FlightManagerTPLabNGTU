package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.FlightModel;
import com.flightmanager.databaseservice.repos.FlightRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;

@RestController
public class FlightController {

    @Autowired
    private FlightRepo repo;


    @GetMapping("${mapping.flight.get}")
    public ResponseEntity<ArrayList<FlightModel>> getAll() {
        try{
            ArrayList<FlightModel> models = (ArrayList<FlightModel>) repo.findAll();
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @GetMapping("${mapping.flight.get}/{id}")
    public ResponseEntity<FlightModel> get(@PathVariable("id") long id) {
        try{
            FlightModel model = repo.findById(id).orElse(null);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }
    @PostMapping("${mapping.flight.create}")
    public ResponseEntity<FlightModel> get(@RequestBody FlightModel data) {
        try{
            data.setId(0L);
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();
            FlightModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.flight.update}")
    public ResponseEntity<FlightModel> update(@RequestBody FlightModel data, @RequestParam("update") String update) {
        try{
            if(data.getId() == null)
                return ResponseEntity.status(400).build();
            FlightModel fromDB = repo.findById(data.getId()).orElse(null);
            if(fromDB == null)
                return ResponseEntity.status(400).build();

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if(!fields.contains("timestampStart"))
                data.setTimestampStart(fromDB.getTimestampStart());
            if(!fields.contains("timestampEnd"))
                data.setTimestampEnd(fromDB.getTimestampEnd());
            if(!fields.contains("dispatcherId"))
                data.setDispatcherId(fromDB.getDispatcherId());
            if(!fields.contains("planeId"))
                data.setPlaneId(fromDB.getPlaneId());
            if(!fields.contains("airportId"))
                data.setAirportId(fromDB.getAirportId());
            if(containsNullFields(data))
                return ResponseEntity.status(400).build();

            FlightModel model = repo.save(data);
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.flight.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try{
            repo.deleteById(id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            e.printStackTrace();
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(FlightModel data){
        return data.getTimestampStart() == null ||
                data.getTimestampEnd() == null ||
                data.getDispatcherId() == null ||
                data.getPlaneId() != null ||
                data.getAirportId() == null;
    }

}
